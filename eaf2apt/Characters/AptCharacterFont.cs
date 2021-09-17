using SwfLib.Shapes.FillStyles;
using SwfLib.Shapes.LineStyles;
using SwfLib.Tags.FontTags;
using System.Collections.Generic;

namespace eaf2apt.Characters
{
    class AptCharacterFont : AptCharacter
    {
        public string FontName;
        public int[] GlyphIds { get; }
        public override void OutputCharacter(int i)
        {
            base.OutputCharacter(i);
            GlobalData.output.Write(3, (int)AptCharacterType.Font);
            GlobalData.output.Write(3, 0x09876543);
            if (FontName.Length != 0)
            {
                GlobalData.output.WriteFixup(3, @$"{GetHashCode()}_FontName");
                GlobalData.output.Align(4);
                GlobalData.output.FixupPointer(4, @$"{GetHashCode()}_FontName");
                GlobalData.output.Write(4, FontName);
            }
            else
            {
                GlobalData.output.Write(3, 0);
            }
            if (GlyphIds is not null && GlyphIds.Length != 0)
            {
                GlobalData.output.Write(3, GlyphIds.Length);
                GlobalData.output.WriteFixup(3, @$"{GetHashCode()}_GlyphIds");
                GlobalData.output.Align(4);
                GlobalData.output.FixupPointer(4, @$"{GetHashCode()}_GlyphIds");
                foreach (var gl in GlyphIds)
                {
                    GlobalData.output.Write(4, gl);
                }
            }
            else
            {
                GlobalData.output.Write(3, 0);
                GlobalData.output.Write(3, 0);
            }
        }
        public AptCharacterFont(DefineFontTag tag, DefineFontInfoBaseTag info, Globals globaldata) : base(globaldata, tag.TagID)
        {
            FontName = info.FontName;
        }
        public AptCharacterFont(DefineFont2BaseTag tag, Globals globaldata) : base(globaldata, tag.TagID)
        {
            FontName = tag.FontName;
            if (tag.UsedInStaticText)
            {
                List<FillStyleRGB> fills = new();
                List<LineStyleRGB> lines = new();
                SolidFillStyleRGB fill = new();
                fill.Color = new SwfLib.Data.SwfRGB { Red = 255, Green = 255, Blue = 255 };
                fills.Add(fill);
                List<int> glyphIds = new();
                foreach (var glyph in tag.Glyphs)
                {
                    int newid = GlobalData.GetNextExtraID();
                    GlobalData.AddExtraCharacter(new AptCharacterShape(glyph.Records, fills, lines, GlobalData, newid));
                    glyphIds.Add(newid);
                }
                GlyphIds = glyphIds.ToArray();
            }
        }
    }
}
