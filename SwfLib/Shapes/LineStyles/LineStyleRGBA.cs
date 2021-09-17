using SwfLib.Data;

namespace SwfLib.Shapes.LineStyles {
    /// <summary>
    /// Represents line style if RGBA color.
    /// </summary>
    public class LineStyleRGBA : ILineStyle {

        /// <summary>
        /// Gets or sets line width;
        /// </summary>
        public ushort Width { get; set; }

        /// <summary>
        /// Gets or sets line color.
        /// </summary>
        public SwfRGBA Color { get; set; }

    }
}
