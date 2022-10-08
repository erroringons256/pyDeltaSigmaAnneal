class circBuf:
    def __init__(self, size, content = [0.0], offset = 0): # content must be a Python list
        self.size = 2 ** size
        self.content = content + (self.size - len(content)) * [0.0]
        self.offset = offset % self.size
    def get(self, i):
        return self.content[(i + self.offset) % self.size]
    def set(self, i, val):
        self.content[(i + self.offset) % self.size] = val
    def roll(self, n): # Rolls backwards in time, so [0] would be the recent sample you input, [1] the one before that, etc.
        self.offset = (self.offset - n) % self.size 