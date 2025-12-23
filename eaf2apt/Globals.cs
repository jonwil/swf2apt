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

using System.Collections.Generic;
using eaf2apt.Characters;

namespace eaf2apt
{
    class Globals
    {
        public int LastID = 0;
        public AptCharacter[] Characters = new AptCharacter[] { };
        public AptCharacter[] AllCharacters;
        public List<AptCharacter> ExtraCharacters = new();
        public Dictionary<int, bool> ReferencedCharacters = new();
        public string geometrydir;
        public string texturesdir;
        public string soundsdir;
        public string videodir;
        public string artdir;
        public byte[] JPEGTables;
        public AptMovie movie;
        public AptOutput output = new();
        public int MaxPasses;
        public ActionWriter writer;
        public Dictionary<int, bool> HitTestShapes = new();
        public bool IsRA3;
        public bool IsTT;
        public int GetNextExtraID()
        {
            return ExtraCharacters.Count + LastID;
        }
        public void AddExtraCharacter(AptCharacter character)
        {
            ExtraCharacters.Add(character);
        }
    }
}
