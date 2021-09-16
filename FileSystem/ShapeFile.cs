using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinalRelert2.Algorithm;
using System.Runtime.InteropServices;

namespace FinalRelert2.FileSystem
{
    class ShapeFile : MemoryFile
    {
        public ShapeFile(byte[] src) : base(src)
        {
        }

        public ShapeFile(string path) : base(path)
        {
        }

        public ushort Width { get { return GetValue<ushort>(0x2); } }
        public ushort Height { get { return GetValue<ushort>(0x4); } }
        public ushort FrameCount { get { return GetValue<ushort>(0x6); } }
        public unsafe ShapeFrameHeader GetFrameHeader(int i)
            => GetValue<ShapeFrameHeader>(0x8 + sizeof(ShapeFrameHeader) * i); 
        public unsafe int* Index {  get { return (int*)(this.Buffer + 0x10); } }
        public unsafe int GetOffset(int i) => this.Index[i << 1] & 0x0FFFFFFF;
        public unsafe int GetRefOffset(int i) => this.Index[i << 1 + 1] & 0x0FFFFFFF;
        public unsafe int GetFormat(int i) => this.Index[i << 1] >> 28;
        public unsafe byte* GetRawImage(int i) => this.Buffer + this.GetOffset(i);
        public byte[] GetDecompressedImage(int i)
        {
            var header = GetFrameHeader(i);
            var cnt = header.Width * header.Height;
            byte[] ret = new byte[cnt];

            unsafe
            {
                switch (header.Flag)
                {
                    case 1:
                        Marshal.Copy((IntPtr)GetRawImage(i), ret, 0, cnt);
                        break;
                    case 2:
                        int _destOffset = 0;
                        byte* ptr = GetRawImage(i);
                        for (int j = 0; j < header.Height; j++)
                        {
                            int _lineLength =  *(short*)ptr - 2;
                            ptr += 2;
                            Marshal.Copy((IntPtr)ptr, ret, _destOffset, _lineLength);
                        }
                        break;
                    case 3:
                        // TODO
                        break;
                }
            }
            

            return ret;
        }
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    struct ShapeFrameHeader
    {
        [FieldOffset(0x0)] public ushort X;
        [FieldOffset(0x2)] public ushort Y;
        [FieldOffset(0x4)] public ushort Width;
        [FieldOffset(0x6)] public ushort Height;
        [FieldOffset(0x8)] public byte Flag;
        [FieldOffset(0x9)] private unsafe fixed byte Gap[0xB];
        [FieldOffset(0x14)] public int Offset;
    }
}
