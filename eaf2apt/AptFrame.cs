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

using eaf2apt.Controls;
using System.Collections.Generic;
namespace eaf2apt
{
    class AptFrame
    {
        public List<AptControl> Controls = new();
        Globals GlobalData;
        public AptFrame(Globals g)
        {
            GlobalData = g;
        }
        public void WriteFrame(int i)
        {
            GlobalData.output.Align(4);
            int controls = Controls.Count;
            GlobalData.output.Write(4, controls);

            if (controls > 0)
            {
                GlobalData.output.WriteFixup(4, @$"{GetHashCode()}_{i}_Controls");
                GlobalData.output.Align(5);
                GlobalData.output.FixupPointer(5, @$"{GetHashCode()}_{i}_Controls");
                for (int j = 0; j < controls; j++)
                {
                    Controls[j].OutputControl(@$"{GetHashCode()}_{i}_Control_{j}", i);
                }
            }
            else
            {
                GlobalData.output.Write(4, 0);
            }
        }
    }
}
