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

namespace eaf2apt.Characters
{
    abstract class AptCharacter
    {
        protected Globals GlobalData;
        public int ID;
        public AptCharacter(Globals globaldata, int id)
        {
            GlobalData = globaldata;
            ID = id;
        }
        public virtual void OutputCharacter(int i)
        {
            GlobalData.output.WriteFixup(2, @$"AptCharacter_{GetHashCode()}");
            GlobalData.output.Align(3);
            GlobalData.output.FixupPointer(3, @$"AptCharacter_{GetHashCode()}");
        }
    }
}
