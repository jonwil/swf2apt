using SwfLib.Tags.ShapeMorphingTags;

namespace eaf2apt.Characters
{
    class AptCharacterMorph : AptCharacter
    {
        public int StartCharID;
        public int EndCharID;
        public override void OutputCharacter(int i)
        {
            base.OutputCharacter(i);
            GlobalData.output.Write(3, (int)AptCharacterType.Morph);
            GlobalData.output.Write(3, 0x09876543);
            GlobalData.output.Write(3, StartCharID);
            GlobalData.output.Write(3, EndCharID);
        }
        public AptCharacterMorph(DefineMorphShapeTag tag, Globals globaldata) : base(globaldata, tag.TagID)
        {
            StartCharID = GlobalData.GetNextExtraID();
            var startshape = new AptCharacterShape(tag.StartShapeRecords, tag.StartFillStyles, tag.StartLineStyles, GlobalData, StartCharID);
            GlobalData.AddExtraCharacter(startshape);
            EndCharID = GlobalData.GetNextExtraID();
            var endshape = new AptCharacterShape(tag.EndShapeRecords, tag.EndFillStyles, tag.EndLineStyles, startshape.CurLineStyleIndex, startshape.CurFillStyle0Index, startshape.CurFillStyle1Index, GlobalData, EndCharID);
            GlobalData.AddExtraCharacter(endshape);
        }
    }
}
