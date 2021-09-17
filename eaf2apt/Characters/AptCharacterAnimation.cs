using SwfLib.Data;
using System.Collections.Generic;
using System.IO;

namespace eaf2apt.Characters
{
    class AptCharacterAnimation : AptCharacter
    {
        public AptMovie movie;
        public double framerate;
        public SwfRect rect;
        public int chars;
        public Dictionary<ConstPointerType, int> constpointers = new();
        List<AptImport> imports;
        List<AptExport> exports;
        public void WriteImportsExports()
        {
            GlobalData.MaxPasses = 3;
            for (GlobalData.output.curpass = 1; GlobalData.output.curpass <= GlobalData.MaxPasses; GlobalData.output.curpass++)
            {
                GlobalData.output.Align(1);
                if (GlobalData.output.curpass == 1)
                {
                    constpointers[ConstPointerType.imports] = GlobalData.output.GetSize();
                }
                foreach (var import in imports)
                {
                    GlobalData.output.WriteFixup(2, @$"main.aImports_{import.GetHashCode()}_URL");
                    GlobalData.output.WriteFixup(2, @$"main.aImports_{import.GetHashCode()}_Name");
                    GlobalData.output.Write(2, (int)import.ID);
                    GlobalData.output.Write(2, 0);
                    GlobalData.output.Align(3);
                    GlobalData.output.FixupPointer(3, @$"main.aImports_{import.GetHashCode()}_URL");
                    string url = import.URL;
                    url = Path.ChangeExtension(url, null);
                    GlobalData.output.Write(3, url);
                    GlobalData.output.Align(3);
                    GlobalData.output.FixupPointer(3, @$"main.aImports_{import.GetHashCode()}_Name");
                    GlobalData.output.Write(3, import.Name);
                }
            }
            GlobalData.MaxPasses = 3;
            for (GlobalData.output.curpass = 1; GlobalData.output.curpass <= GlobalData.MaxPasses; GlobalData.output.curpass++)
            {
                GlobalData.output.Align(1);
                if (GlobalData.output.curpass == 1)
                {
                    constpointers[ConstPointerType.exports] = GlobalData.output.GetSize();
                }
                int i = 0;
                foreach (var export in exports)
                {
                    i++;
                    GlobalData.output.WriteFixup(2, @$"main.aExports_{export.GetHashCode()}_{i}_Name");
                    GlobalData.output.Write(2, (int)export.ID);
                    GlobalData.output.Align(3);
                    GlobalData.output.FixupPointer(3, @$"main.aExports_{export.GetHashCode()}_{i}_Name");
                    GlobalData.output.Write(3, export.Name);
                }
            }
        }

        public override void OutputCharacter(int i)
        {
            base.OutputCharacter(i);
            GlobalData.output.Write(3, (int)AptCharacterType.Animation);
            GlobalData.output.Write(3, 0x09876543);
            movie.WriteMovieFrames();
            GlobalData.output.Write(3, chars);
            GlobalData.output.Write(3, constpointers[ConstPointerType.characters]);
            GlobalData.output.Write(3, rect.XMax / 20);
            GlobalData.output.Write(3, rect.YMax / 20);
            GlobalData.output.Write(3, (int)(1000 / framerate));
            GlobalData.output.Write(3, imports.Count);
            GlobalData.output.Write(3, constpointers[ConstPointerType.imports]);
            GlobalData.output.Write(3, exports.Count);
            GlobalData.output.Write(3, constpointers[ConstPointerType.exports]);
            GlobalData.output.Write(3, 0);
        }
        public AptCharacterAnimation(AptMovie mov, Globals globaldata, int id, double fr, SwfRect r, int c, List<AptImport> i, List<AptExport> e) : base(globaldata, id)
        {
            movie = mov;
            framerate = fr;
            rect = r;
            chars = c;
            imports = i;
            exports = e;
        }
    }
}
