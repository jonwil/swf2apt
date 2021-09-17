using System;
using SwfLib.Data;
using SwfLib.Utils;

namespace SwfLib {
    public static class SwfStreamWriterExt {

        public static void WriteSwfFileInfo(this ISwfStreamWriter writer, SwfFileInfo fileInfo) {
            string format = fileInfo.Format.ToString();
            if (string.IsNullOrEmpty(format) || format.Length != 3)
                throw new InvalidOperationException("Format should be of length 3");
            writer.WriteByte((byte)format[0]);
            writer.WriteByte((byte)format[1]);
            writer.WriteByte((byte)format[2]);

            writer.WriteByte(fileInfo.Version);

            var len = fileInfo.FileLength;
            writer.WriteByte((byte)((len >> 0) & 0xff));
            writer.WriteByte((byte)((len >> 8) & 0xff));
            writer.WriteByte((byte)((len >> 16) & 0xff));
            writer.WriteByte((byte)((len >> 24) & 0xff));
        }
    }
}
