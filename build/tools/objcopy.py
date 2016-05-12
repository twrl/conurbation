import sys
import os

if __name__ == "__main__":
   os.execvp("/usr/bin/objcopy", ["objcopy"] + sys.argv[1:])
