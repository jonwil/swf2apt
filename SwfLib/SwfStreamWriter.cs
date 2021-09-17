using System;
using System.IO;
using System.Text;

namespace SwfLib {
    /// <summary>
    /// Represends writer for swf file primitives.
    /// </summary>
    public class SwfStreamWriter : ISwfStreamWriter {

        private readonly BinaryWriter _writer;
        private readonly Stream _baseStream;

        /// <summary>
        /// Initializes a new instance of the <see cref="SwfStreamWriter"/> class.
        /// </summary>
        /// <param name="stream">The stream.</param>
        public SwfStreamWriter(Stream stream) {
            _writer = new BinaryWriter(stream);
            _baseStream = stream;
        }

        public void Flush() {
            _writer.Flush();
        }

        public void WriteBytes(byte[] bytes)
        {
            _writer.Write(bytes);
        }

        public void WriteByte(byte val)
        {
            _writer.Write(val);
        }
    }
}
