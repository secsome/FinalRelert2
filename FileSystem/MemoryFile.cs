using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.InteropServices;
using FinalRelert2.Interfaces;

namespace FinalRelert2.FileSystem
{
    unsafe class MemoryFile : IRelease
    {
        
        public MemoryFile(byte[] src)
        {
            this.buffer = src;
        }

        public MemoryFile(string path)
        {
            this.buffer = File.Exists(path) ? File.ReadAllBytes(path) : null;
        }

        public bool Release()
        {
            this.buffer = null;
            return true;
        }

        protected void GetByteAt(int at, int len, IntPtr ptr)
        {
            Marshal.Copy(buffer, at, ptr, len);
        }

        protected T GetValue<T>(int at) where T : unmanaged
        {
            T ret;
            GetByteAt(at, sizeof(T), new IntPtr(&ret));
            return ret;
        }

        protected T[] GetArray<T>(int at, int len) where T : unmanaged
        {
            T[] ret = new T[len];
            for (int i = 0; i < len; ++i)
                ret[i] = GetValue<T>(at + i * sizeof(T));
            return ret;
        }

        public bool IsValid { get { return buffer != null; } }

        private byte[] buffer;
    }
}
