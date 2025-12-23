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

using SwfLib.Tags.ButtonTags;
using System.Collections.Generic;

namespace eaf2apt.Characters
{
    class AptCharacterButton : AptCharacter
    {
        public DefineButton2Tag Tag;
        public AptRect Bounds;
        public float[] Vertices;
        public short[] Indices;
        void FindIndex(List<float> verts, List<short> indexes, float x, float y)
        {
            int length = verts.Count;
            int index = -1;

            for (short i = 0; i < length; i += 2)
            {
                if (verts[i] == x && verts[i + 1] == y)
                {
                    index = i / 2;
                    break;
                }
            }

            if (index == -1)
            {
                verts.Add(x);
                verts.Add(y);
                index = length / 2;
            }

            indexes.Add((short)index);
        }
        public void UpdateHitTestShape()
        {
            Bounds = new AptRect { fTop = 0, fLeft = 0, fBottom = -1, fRight = -1 };
            List<float> verts = new();
            List<short> indices = new();

            foreach (var br in Tag.Characters)
            {
                if (br.StateHitTest)
                {
                    if (GlobalData.AllCharacters[br.CharacterID] is AptCharacterShape hit)
                    {
                        Bounds = hit.BoundingRect;

                        foreach (var shape in hit.shapes)
                        {
                            foreach (var tri in shape.triangles)
                            {
                                FindIndex(verts, indices, (float)tri.a.X / 20.0f, (float)tri.a.Y / 20.0f);
                                FindIndex(verts, indices, (float)tri.b.X / 20.0f, (float)tri.b.Y / 20.0f);
                                FindIndex(verts, indices, (float)tri.c.X / 20.0f, (float)tri.c.Y / 20.0f);
                            }
                        }
                    }
                }
            }

            Vertices = verts.ToArray();
            Indices = indices.ToArray();
        }
        public override void OutputCharacter(int i)
        {
            base.OutputCharacter(i);
            GlobalData.output.Write(3, (int)AptCharacterType.Button);
            GlobalData.output.Write(3, 0x09876543);

            if (GlobalData.IsTT)
            {
                GlobalData.output.Write(3, 0x0);
                GlobalData.output.Write(3, 0x0);
            }

            GlobalData.output.Write(3, Tag.TrackAsMenu);
            GlobalData.output.Write(3, Bounds);
            GlobalData.output.Write(3, Indices.Length / 3);
            GlobalData.output.Write(3, Vertices.Length / 2);
            GlobalData.output.WriteFixup(3, @$"{i}_HitTestVertexTable");
            GlobalData.output.WriteFixup(3, @$"{i}_HitTestIndexTable");
            GlobalData.output.Align(4);
            GlobalData.output.FixupPointer(4, @$"{i}_HitTestVertexTable");

            foreach (var v in Vertices)
            {
                GlobalData.output.Write(4, (float)v);
            }

            GlobalData.output.Align(4);
            GlobalData.output.FixupPointer(4, @$"{i}_HitTestIndexTable");

            foreach (var ind in Indices)
            {
                GlobalData.output.Write(4, (ushort)ind);
            }

            GlobalData.output.Write(3, Tag.Characters.Count);
            GlobalData.output.WriteFixup(3, @$"{GetHashCode()}_Characters");
            GlobalData.output.Write(3, Tag.Conditions.Count);
            GlobalData.output.WriteFixup(3, @$"{GetHashCode()}_Conditions");
            GlobalData.output.Write(3, 0);
            GlobalData.output.Align(4);
            GlobalData.output.FixupPointer(4, @$"{GetHashCode()}_Characters");

            foreach (var br in Tag.Characters)
            {
                GlobalData.output.Align(4);
                GlobalData.output.Write(4, (int)br.States);
                GlobalData.output.Write(4, (int)br.CharacterID);
                GlobalData.output.Write(4, (int)br.PlaceDepth);
                GlobalData.output.Write(4, br.PlaceMatrix);
                GlobalData.output.Write(4, br.ColorTransform);
            }

            GlobalData.output.Align(4);
            GlobalData.output.FixupPointer(4, @$"{GetHashCode()}_Conditions");

            foreach (var ar in Tag.Conditions)
            {
                GlobalData.output.Write(4, (int)ar.Conditions);
                GlobalData.writer.WriteActions(4, @$"{GetHashCode()}_{ar.GetHashCode()}_Actions", ar.Actions);
            }
        }
        public AptCharacterButton(DefineButton2Tag tag, Globals globaldata) : base(globaldata, tag.TagID)
        {
            Tag = tag;
        }
    }
}
