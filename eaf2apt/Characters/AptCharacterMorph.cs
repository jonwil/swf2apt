/*
**	swf2apt
**	Copyright 2025 Jonathan Wilson
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

            if (GlobalData.IsTT)
            {
                GlobalData.output.Write(3, 0x0);
                GlobalData.output.Write(3, 0x0);
            }

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
