using SwfLib.Data;
using SwfLib.Tags.TextTags;
using System.Collections.Generic;

namespace eaf2apt.Characters
{
    class StaticTextRecord
    {
        public ushort FontID;
        public AptFloatArrayCXForm CXForm;
        public short XOffset;
        public short YOffset;
        public float Scale;
        public List<AptCharacterGlyphEntry> Glyphs;
    }
    class AptCharacterStaticText : AptCharacter
    {
        public AptRect BoundingRect;
        public SwfMatrix Matrix;
        public List<StaticTextRecord> Records = new();
        public override void OutputCharacter(int i)
        {
            base.OutputCharacter(i);
            GlobalData.output.Write(3, (int)AptCharacterType.StaticText);
            GlobalData.output.Write(3, 0x09876543);
            GlobalData.output.Write(3, BoundingRect);
            GlobalData.output.Write(3, Matrix);
            GlobalData.output.Write(3, Records.Count);
            GlobalData.output.WriteFixup(3, @$"{GetHashCode()}_Records");
            GlobalData.output.Align(4);
            GlobalData.output.FixupPointer(4, @$"{GetHashCode()}_Records");
            foreach (var r in Records)
            {
                GlobalData.output.Write(4, (int)r.FontID);
                GlobalData.output.Write(4, r.CXForm);
                GlobalData.output.Write(4, r.XOffset / 20.0f);
                GlobalData.output.Write(4, r.YOffset / 20.0f);
                GlobalData.output.Write(4, r.Scale);
                GlobalData.output.Write(4, r.Glyphs.Count);
                GlobalData.output.WriteFixup(4, @$"{GetHashCode()}_{r.GetHashCode()}_Glyphs");
                GlobalData.output.Align(5);
                GlobalData.output.FixupPointer(5, @$"{GetHashCode()}_{r.GetHashCode()}_Glyphs");
                foreach (var gl in r.Glyphs)
                {
                    GlobalData.output.Write(5, (ushort)gl.nIndex);
                    GlobalData.output.Write(5, (ushort)gl.nAdvance);
                }
            }
        }
        unsafe public AptCharacterStaticText(DefineTextTag tag, Globals globaldata) : base(globaldata, tag.TagID)
        {
            BoundingRect = new AptRect { fLeft = tag.TextBounds.XMin / 20.0f, fTop = tag.TextBounds.YMin / 20.0f, fRight = tag.TextBounds.XMax / 20.0f, fBottom = tag.TextBounds.YMax / 20.0f };
            Matrix = tag.TextMatrix;
            foreach (var record in tag.TextRecords)
            {
                StaticTextRecord outrecord = new();
                outrecord.Glyphs = new();
                outrecord.FontID = 0;
                if (record.FontID is not null)
                {
                    outrecord.FontID = record.FontID.Value;
                }
                outrecord.CXForm.scale[0] = 0;
                outrecord.CXForm.scale[1] = 0;
                outrecord.CXForm.scale[2] = 0;
                outrecord.CXForm.scale[3] = 0;
                outrecord.CXForm.translate[0] = 0;
                outrecord.CXForm.translate[1] = 0;
                outrecord.CXForm.translate[2] = 0;
                outrecord.CXForm.translate[3] = 0;
                if (record.TextColor is not null)
                {
                    outrecord.CXForm.scale[0] = 255;
                    outrecord.CXForm.scale[1] = record.TextColor.Value.Red;
                    outrecord.CXForm.scale[2] = record.TextColor.Value.Green;
                    outrecord.CXForm.scale[3] = record.TextColor.Value.Blue;
                }
                outrecord.XOffset = 0;
                if (record.XOffset is not null)
                {
                    outrecord.XOffset = record.XOffset.Value;
                }
                outrecord.YOffset = 0;
                if (record.YOffset is not null)
                {
                    outrecord.YOffset = record.YOffset.Value;
                }
                outrecord.Scale = 1;
                if (record.TextHeight is not null)
                {
                    outrecord.Scale = record.TextHeight.Value / 1000.0f;
                }
                foreach (var glyph in record.Glyphs)
                {
                    AptCharacterGlyphEntry outglyph;
                    outglyph.nAdvance = (short)glyph.GlyphAdvance;
                    outglyph.nIndex = (short)glyph.GlyphIndex;
                    outrecord.Glyphs.Add(outglyph);
                }
                Records.Add(outrecord);
            }
        }
        unsafe public AptCharacterStaticText(DefineText2Tag tag, Globals globaldata) : base(globaldata, tag.TagID)
        {
            BoundingRect = new AptRect { fLeft = tag.TextBounds.XMin / 20.0f, fTop = tag.TextBounds.YMin / 20.0f, fRight = tag.TextBounds.XMax / 20.0f, fBottom = tag.TextBounds.YMax / 20.0f };
            Matrix = tag.TextMatrix;
            foreach (var record in tag.TextRecords)
            {
                StaticTextRecord outrecord = new();
                outrecord.FontID = 0;
                if (record.FontID is not null)
                {
                    outrecord.FontID = record.FontID.Value;
                }
                outrecord.CXForm.scale[0] = 0;
                outrecord.CXForm.scale[1] = 0;
                outrecord.CXForm.scale[2] = 0;
                outrecord.CXForm.scale[3] = 0;
                outrecord.CXForm.translate[0] = 0;
                outrecord.CXForm.translate[1] = 0;
                outrecord.CXForm.translate[2] = 0;
                outrecord.CXForm.translate[3] = 0;
                if (record.TextColor is not null)
                {
                    outrecord.CXForm.scale[0] = record.TextColor.Value.Alpha;
                    outrecord.CXForm.scale[1] = record.TextColor.Value.Red;
                    outrecord.CXForm.scale[2] = record.TextColor.Value.Green;
                    outrecord.CXForm.scale[3] = record.TextColor.Value.Blue;
                }
                outrecord.XOffset = 0;
                if (record.XOffset is not null)
                {
                    outrecord.XOffset = record.XOffset.Value;
                }
                outrecord.YOffset = 0;
                if (record.YOffset is not null)
                {
                    outrecord.YOffset = record.YOffset.Value;
                }
                outrecord.Scale = 1;
                if (record.TextHeight is not null)
                {
                    outrecord.Scale = record.TextHeight.Value / 1000.0f;
                }
                foreach (var glyph in record.Glyphs)
                {
                    AptCharacterGlyphEntry outglyph;
                    outglyph.nAdvance = (short)glyph.GlyphAdvance;
                    outglyph.nIndex = (short)glyph.GlyphIndex;
                    outrecord.Glyphs.Add(outglyph);
                }
                Records.Add(outrecord);
            }
        }
    }
}
