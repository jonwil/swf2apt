using System;
using System.Collections.Generic;
using System.IO;
using SwfLib.Data;
using SwfLib.Tags;

namespace SwfLib {
    public class SwfFile {

        public SwfFileInfo FileInfo;

        public SwfHeader Header;

        /// <summary>
        /// Gets list of tags.
        /// </summary>
        public readonly List<SwfTagBase> Tags = new List<SwfTagBase>();

        public static SwfFile ReadFrom(Stream stream) {
            var file = new SwfFile();
            ISwfStreamReader reader = new SwfStreamReader(stream);
            file.FileInfo = reader.ReadSwfFileInfo();
            reader = GetSwfStreamReader(file.FileInfo, stream);
            file.Header = reader.ReadSwfHeader();
            ReadTags(file, reader);
            return file;
        }

        public static void Decompress(Stream source, Stream target) {
            var reader = new SwfStreamReader(source);
            var outputWriter = new SwfStreamWriter(target);

            var fileInfo = reader.ReadSwfFileInfo();

            if (fileInfo.Format == SwfFormat.Unknown) {
                throw new NotSupportedException("Illegal file format");
            }

            var rest = reader.ReadRest();
            if (fileInfo.Format == SwfFormat.FWS) {
                outputWriter.WriteSwfFileInfo(fileInfo);
                outputWriter.WriteBytes(rest);
                return;
            }

            var uncompressed = new MemoryStream();
            SwfZip.Decompress(new MemoryStream(rest), uncompressed, fileInfo.Format);

            outputWriter.WriteSwfFileInfo(new SwfFileInfo {
                Format = SwfFormat.FWS,
                FileLength = (uint)(uncompressed.Length + 8),
                Version = fileInfo.Version
            });
            outputWriter.WriteBytes(uncompressed.ToArray());
            outputWriter.Flush();
        }

        private static void ReadTags(SwfFile file, ISwfStreamReader reader) {
            while (!reader.IsEOF) {
                var ser = new SwfTagDeserializer(file);
                var tagData = reader.ReadTagData();
                SwfTagBase tag = ser.ReadTag(tagData);
                if (tag != null) file.Tags.Add(tag);
                else throw new InvalidOperationException("Tag can't be null. Loss of data possible");
            }
        }

        protected static ISwfStreamReader GetSwfStreamReader(SwfFileInfo info, Stream stream) {
            if (info.Format == SwfFormat.FWS) {
                return new SwfStreamReader(stream);
            }

            MemoryStream memoryStream = new MemoryStream();
            SwfZip.Decompress(stream, memoryStream, info.Format);
            return new SwfStreamReader(memoryStream);
        }

    }
}
