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

        protected MemoryFile(byte[] src)
        {
            this.Buffer = (byte*)Marshal.AllocHGlobal(src.Length);
            Marshal.Copy(src, 0, (IntPtr)this.Buffer, src.Length);
            this.Length = src.Length;
        }

        protected MemoryFile(string path)
        {
            if(File.Exists(path))
            {
                var src = File.ReadAllBytes(path);
                this.Buffer = (byte*)Marshal.AllocHGlobal(src.Length);
                Marshal.Copy(src, 0, (IntPtr)this.Buffer, src.Length);
                this.Length = src.Length;
            }
        }

        public bool Release()
        {
            Marshal.FreeHGlobal((IntPtr)this.Buffer);
            this.Buffer = null;
            this.Length = 0;
            return true;
        }

        protected T GetValue<T>(int at) where T : unmanaged
        {
            return *(T*)this.Buffer[at];
        }

        protected T[] GetArray<T>(int at, int len) where T : unmanaged
        {
            T[] ret = new T[len];
            for (int i = 0; i < len; ++i)
                ret[i] = GetValue<T>(at + i * sizeof(T));
            return ret;
        }

        protected bool IsValid { get { return Buffer != null && this.Length != 0; } }

        protected byte* Buffer { get; set; }
        protected int Length { get; set; }
    }
}
