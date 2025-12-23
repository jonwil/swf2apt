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

namespace eaf2apt.Controls
{
    abstract class AptControl
    {
        protected Globals GlobalData;
        public AptControl(Globals globaldata)
        {
            GlobalData = globaldata;
        }
        public virtual void OutputControl(string str, int i)
        {
            GlobalData.output.WriteFixup(5, str);
            GlobalData.output.Align(6);
            GlobalData.output.FixupPointer(6, str);
        }
    }
}
