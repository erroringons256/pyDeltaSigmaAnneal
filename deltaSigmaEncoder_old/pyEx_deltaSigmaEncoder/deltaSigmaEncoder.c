#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#endif
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include "circBuf.h"
#include "deltaSigmaEncoder.h"

char encoder_init(encoder* self, unsigned int fSize, unsigned int bufSize, double* xFilter, double* yFilter)
{
	self->xFilter = malloc(fSize * sizeof(double));
	self->yFilter = malloc(fSize * sizeof(double));

	if(self->xFilter == 0)
	{
		return(1);
	}
	else
	{
		memcpy(self->xFilter, xFilter, fSize * sizeof(double));
	}
	if (self->yFilter == 0)
	{
		return(1);
	}
	else
	{
		memcpy(self->yFilter, yFilter, fSize * sizeof(double));
	}
	
}

void encoder_encode(encoder* self, unsigned int n, double* inSignal, double* outSignal)
{
}

static unsigned long long cfib(unsigned int n, unsigned long long a, unsigned long long b)
{
	unsigned long long c;
	while (n-- > 0)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return b;
}

static void cDemoCircBuf(unsigned char maskLen)
{
	circBuf buf;
	circBuf_init(&buf, maskLen);
	circBuf_set(&buf, 0, 1.0);
	for (unsigned int i = 0; i < 16; i++)
	{
		printf("[");
		for (unsigned int j = 0; j < 8; j++)
		{
			printf(" %lf", circBuf_get(&buf, j));
		}
		printf(" ]\n");
		circBuf_roll(&buf, 1);
	}
}

// static PyObject* abstractFib(unsigned int n) // This entire function is really a mistake and was only written for practice purposes, USE A PROPER ARBITRARY PRECISION LIBRARY!
// {
// 	PyObject* a = PyLong_FromLong(1);
// 	PyObject* b = PyLong_FromLong(0);
// 	PyObject* c;
// 	
// 	while (n-- > 0)
// 	{
// 		c = PyNumber_Add(a, b);
// 		Py_DECREF(a);
// 		a = b;
// 		b = c;
// 	}
// 	Py_DECREF(a);
// 	return b;
// }


static PyObject* pyfib(PyObject* self, PyObject* arg, PyObject* kwarg)
{
	// Initialise to default Fibonacci values in case no other arguments are specified.
	unsigned long long a = 1;
	unsigned long long b = 0;
	unsigned int n;
	static char* keyword[] = { "n", "a", "b", NULL };
	// Parse and return NULL in case parsing fails.
	if (!PyArg_ParseTupleAndKeywords(arg, kwarg, "I|KK:fib", keyword, &n, &a, &b))
	{
		return NULL;
	}
	if (PyErr_Occurred())
	{
		return NULL;
	}

	return PyLong_FromUnsignedLongLong(cfib(n, a, b));
}

static PyObject* demoCircBuf()
{
	cDemoCircBuf(3);
	Py_RETURN_NONE;
}

PyDoc_STRVAR(fibDoc, "Computes the nth Fibonacci number by recursion.");
PyDoc_STRVAR(demoCircBufDoc, "Demonstrates a ring buffer working.");

PyMethodDef fibMethod[] =
{
	{"fib", (PyCFunction)pyfib, METH_VARARGS | METH_KEYWORDS, fibDoc},// module method name, method that gets called, method type, docstring
	{"demoCircBuf", (PyCFunction)demoCircBuf, METH_NOARGS, demoCircBufDoc},
	{NULL, NULL, 0, NULL}
};

PyDoc_STRVAR(fibModuleDoc, "Provides a Fibonacci function.");

PyModuleDef fibModule =
{ PyModuleDef_HEAD_INIT,"fib", fibModuleDoc, -1, fibMethod, NULL, NULL, NULL, NULL }; // Head, module name, docstring, global state size, method array, state mgmt functions

PyMODINIT_FUNC PyInit_fib(void)
{
	return PyModule_Create(&fibModule);
}