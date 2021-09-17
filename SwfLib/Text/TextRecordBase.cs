﻿using System.Collections.Generic;

namespace SwfLib.Text {
    public abstract class TextRecordBase {

        public bool Type;

        public byte Reserved { get; set; }

        public bool IsEnd {
            get { return !Type && Reserved == 0; }
        }

        public ushort? FontID;

        public short? XOffset;

        public short? YOffset;

        public ushort? TextHeight;

        /// <summary>
        /// Gets list of glyphs.
        /// </summary>
        public readonly List<GlyphEntry> Glyphs = new List<GlyphEntry>();

    }
}
