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
