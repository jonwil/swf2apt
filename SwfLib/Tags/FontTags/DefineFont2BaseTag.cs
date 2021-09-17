using System.Collections.Generic;
using SwfLib.Fonts;

namespace SwfLib.Tags.FontTags
{
    public abstract class DefineFont2BaseTag : DefineFontBaseTag
    {
        public byte Language { get; set; }

        /// <summary>
        /// Gets or sets the name of the font.
        /// </summary>
        /// <value>
        /// The name of the font.
        /// </value>
        public string FontName { get; set; }

        public bool HasLayout { get; set; }

        public bool ShiftJIS { get; set; }

        public bool SmallText { get; set; }

        public bool ANSI { get; set; }

        public bool WideOffsets { get; set; }

        public bool WideCodes { get; set; }

        public bool Italic { get; set; }

        public bool Bold { get; set; }


        public short Ascent { get; set; }

        public short Descent { get; set; }

        public short Leading { get; set; }

        public readonly List<Glyph> Glyphs = new List<Glyph>();

        public readonly List<KerningRecord> KerningRecords = new List<KerningRecord>();

    }
}
