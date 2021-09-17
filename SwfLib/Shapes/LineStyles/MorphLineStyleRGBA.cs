using SwfLib.Data;

namespace SwfLib.Shapes.LineStyles
{
    public class MorphLineStyleRGBA : ILineStyle
    {

        public ushort StartWidth { get; set; }
        public ushort EndWidth { get; set; }

        public SwfRGBA StartColor { get; set; }
        public SwfRGBA EndColor { get; set; }
    }
}
