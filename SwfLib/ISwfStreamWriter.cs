namespace SwfLib {
    /// <summary>
    /// Represents interface for writing swf file primitives.
    /// </summary>
    public interface ISwfStreamWriter {
        void WriteByte(byte val);
    }
}
