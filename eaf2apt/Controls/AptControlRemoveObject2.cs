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

using SwfLib.Tags.DisplayListTags;

namespace eaf2apt.Controls
{
    class AptControlRemoveObject2 : AptControl
    {
        public RemoveObject2Tag Tag;
        public AptControlRemoveObject2(RemoveObject2Tag tag, Globals globaldata) : base(globaldata)
        {
            Tag = tag;
        }
        public override void OutputControl(string str, int i)
        {
            base.OutputControl(str, i);
            GlobalData.output.Write(6, (int)AptControlType.RemoveObject2);
            GlobalData.output.Align(6);
            GlobalData.output.Write(6, (int)Tag.Depth);
        }
    }
}
