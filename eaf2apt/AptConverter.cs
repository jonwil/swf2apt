using eaf2apt.Characters;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Diagnostics;
using System.IO;
using SwfLib;
using SwfLib.Tags;
using SwfLib.Tags.BitmapTags;
using SwfLib.Tags.ButtonTags;
using SwfLib.Tags.ControlTags;
using SwfLib.Tags.FontTags;
using SwfLib.Tags.ShapeTags;
using SwfLib.Tags.ShapeMorphingTags;
using SwfLib.Tags.SoundTags;
using SwfLib.Tags.TextTags;
using SwfLib.Tags.VideoTags;
using TGASharpLib;

namespace eaf2apt
{
    enum ConstPointerType
    {
        imports = 0,
        exports = 1,
        characters = 2,
        maincharacter = 3
    };
    class AptConverter
    {
        Globals GlobalData;
        List<AptCharacterBitmap> bitmaps = new();
        List<AptCharacterShape> shapes = new();
        List<string> TextureIDs = new();
        List<string> NoPackedStrings = new();
        List<string> PackedStrings = new();
        List<string> ShapeIDs = new();

        public ushort Find_POT(ushort x)
        {
            ushort i = 1;
            while (i <= x)
            {
                i *= 2;
            }
            return i;
        }
        public void CopyToBuffer(Image src, Image dest, int x, int y)
        {
            var b = new Bitmap(src.Width + 2, src.Height + 2, src.PixelFormat);
            Graphics g = Graphics.FromImage(b);
            g.DrawImage(src, 1, 1, src.Width, src.Height);
            Graphics g2 = Graphics.FromImage(dest);
            g2.DrawImage(b, x, y, b.Width, b.Height);
        }
        public void Resize(string input, string output)
        {
            TGA intga = new TGA(input);
            ushort srcwidth = intga.Width;
            ushort srcheight = intga.Height;
            ushort destwidth = Find_POT((ushort)(intga.Width + 2));
            ushort destheight = Find_POT((ushort)(intga.Height + 2));
            int bpp = ((int)intga.Header.ImageSpec.PixelDepth) / 8;
            Bitmap src = intga.ToBitmap();
            Bitmap dest = new Bitmap(destwidth, destheight, src.PixelFormat);
            CopyToBuffer(src, dest, 0, 0);
            TGA outtga = TGA.FromBitmap(dest, false, false);
            outtga.Header.ColorMapSpec.ColorMapEntrySize = TgaColorMapEntrySize.A8R8G8B8;
            outtga.Save(output);
        }
        public void ResizeNoPack(int id, string input, string output)
        {
            TGA intga = new TGA(input);
            NoPackedStrings.Add(@$"{id}=0 0 {intga.Width} {intga.Height}");
            ushort srcwidth = intga.Width;
            ushort srcheight = intga.Height;
            ushort destwidth = Find_POT(srcwidth);
            ushort destheight = Find_POT(srcheight);
            int bpp = ((int)intga.Header.ImageSpec.PixelDepth) / 8;
            TGA outtga = new TGA(destwidth, destheight, intga.Header.ImageSpec.PixelDepth, intga.Header.ImageType, intga.Header.ImageSpec.ImageDescriptor.AlphaChannelBits, false);
            outtga.Header.ColorMapSpec.ColorMapEntrySize = TgaColorMapEntrySize.A8R8G8B8;
            byte[] target = new byte[destwidth * destheight * bpp];
            byte[] source = intga.ImageOrColorMapArea.ImageData;
            for (int i = 0; i < destheight; i++)
            {
                for (int j = 0; j < destwidth; j++)
                {
                    int x = i;
                    if (x >= srcheight)
                    {
                        x = srcheight - 1;
                    }
                    int y = j;
                    if (y >= srcwidth)
                    {
                        y = srcwidth - 1;
                    }
                    int src = ((srcheight - x - 1) * srcwidth * bpp) + (y * bpp);
                    int dest = ((destheight - i - 1) * destwidth * bpp) + (j * bpp);
                    for (int k = 0; k < bpp; k++)
                    {
                        target[dest + k] = source[src + k];
                    }
                }
            }
            outtga.ImageOrColorMapArea.ImageData = target;
            outtga.Save(output);
        }
        public void PackTextures(string basename)
        {
            foreach (var b in bitmaps)
            {
                if (b.Tga)
                {
                    TextureIDs.Add(b.ID.ToString());
                    if (b.NoPack)
                    {
                        string name = b.TextureName;
                        string name2 = Path.ChangeExtension(b.TextureName, ".tga.noPack");
                        File.Move(name, name2);
                        string outname = @$"{GlobalData.artdir}\apt_{basename}_{b.ID}.tga";
                        ResizeNoPack(b.ID, name2, outname);
                        b.PackOffset.X = 0;
                        b.PackOffset.Y = 0;
                    }
                    else
                    {
                        string name = b.TextureName;
                        string outname = @$"{GlobalData.artdir}\apt_{basename}_{b.ID}.tga";
                        PackedStrings.Add(@$"{b.ID}->{b.ID}");
                        Resize(name, outname);
                        b.PackOffset.X = 1;
                        b.PackOffset.Y = 1;
                    }
                }
            }
        }
        void FindButtonHitTest()
        {
            for (int i = 0; i < GlobalData.AllCharacters.Length; i++)
            {
                if (GlobalData.AllCharacters[i] is AptCharacterButton button)
                {
                    foreach (var record in button.Tag.Characters)
                    {
                        if (record.StateDown || record.StateOver || record.StateUp)
                        {
                            GlobalData.ReferencedCharacters[record.CharacterID] = true;
                        }
                        if (record.StateHitTest)
                        {
                            GlobalData.HitTestShapes[record.CharacterID] = true;
                        }
                    }
                }
            }
        }

        public void ConvertToApt(string filename, bool optimize, bool isra3)
        {
            string basename = filename;
            basename = Path.ChangeExtension(basename, null);
            if (optimize)
            {
                if (Path.GetExtension(filename) != ".eaf")
                {
                    string ra3 = "";
                    if (isra3)
                    {
                        ra3 = "--ra3";
                    }
                    string optname = basename + ".eaf";
                    var process = Process.Start("flasm", @$"{filename} {optname} {ra3}");
                    process.WaitForExit();
                    int last = process.ExitCode;
                    process = Process.Start("flasm", @$"{optname} {optname} {ra3}");
                    process.WaitForExit();
                    int current = process.ExitCode;
                    while (last != current)
                    {
                        last = current;
                        process = Process.Start("flasm", @$"{optname} {optname} {ra3}");
                        process.WaitForExit();
                        current = process.ExitCode;
                    }
                    filename = optname;
                }
            }
            GlobalData = new Globals();
            GlobalData.writer = new ActionWriter(GlobalData);
            GlobalData.geometrydir = basename + "_geometry";
            GlobalData.texturesdir = basename + "_textures";
            GlobalData.soundsdir = basename + "_sounds";
            GlobalData.videodir = basename + "_videos";
            GlobalData.artdir = basename + "_art";
            if (Directory.Exists(GlobalData.geometrydir))
            {
                Directory.Delete(GlobalData.geometrydir, true);
            }
            if (Directory.Exists(GlobalData.texturesdir))
            {
                Directory.Delete(GlobalData.texturesdir, true);
            }
            if (Directory.Exists(GlobalData.soundsdir))
            {
                Directory.Delete(GlobalData.soundsdir, true);
            }
            if (Directory.Exists(GlobalData.videodir))
            {
                Directory.Delete(GlobalData.videodir, true);
            }
            if (Directory.Exists(GlobalData.artdir))
            {
                Directory.Delete(GlobalData.artdir, true);
            }
            Directory.CreateDirectory(GlobalData.geometrydir);
            Directory.CreateDirectory(GlobalData.texturesdir);
            Directory.CreateDirectory(GlobalData.soundsdir);
            Directory.CreateDirectory(GlobalData.videodir);
            Directory.CreateDirectory(GlobalData.artdir);
            using (var source = File.Open(filename, FileMode.Open, FileAccess.Read))
            {
                var swf = SwfFile.ReadFrom(source);
                List<SwfTagBase> CharacterList = new();
                List<ImportAssetsBase> ImportAssetsList = new();
                List<ExportAssetsTag> ExportAssetsList = new();
                List<DefineTextTag> DefineTextList = new();
                List<DefineText2Tag> DefineText2List = new();
                Dictionary<int, DefineFontInfoBaseTag> DefineFontInfoList = new();
                Dictionary<int, DefineFontBaseTag> FontBaseList = new();
                foreach (var item in swf.Tags)
                {
                    if (!item.IsControlTag)
                    {
                        CharacterList.Add(item);
                    }
                    switch (item)
                    {
                        case ImportAssetsBase import:
                            ImportAssetsList.Add(import);
                            break;
                        case ExportAssetsTag export:
                            ExportAssetsList.Add(export);
                            break;
                        case DefineTextTag definetext:
                            DefineTextList.Add(definetext);
                            break;
                        case DefineText2Tag definetext2:
                            DefineText2List.Add(definetext2);
                            break;
                        case DefineFontInfoBaseTag definefontinfo:
                            DefineFontInfoList.Add(item.TagID, definefontinfo);
                            break;
                        case DefineFontBaseTag definefont:
                            FontBaseList.Add(item.TagID, definefont);
                            break;
                    }
                }
                foreach (var item in CharacterList)
                {
                    var id = item.TagID;
                    if (id > GlobalData.LastID)
                    {
                        GlobalData.LastID = id;
                    }
                }
                GlobalData.LastID++;
                foreach (var import in ImportAssetsList)
                {
                    foreach (var i in import.Tags)
                    {
                        if (i >= GlobalData.LastID)
                        {
                            GlobalData.LastID++;
                        }
                    }
                }

                Array.Resize(ref GlobalData.Characters, GlobalData.LastID);

                foreach (var text in DefineTextList)
                {
                    foreach (var i in text.TextRecords)
                    {
                        if (i.FontID is not null)
                        {
                            FontBaseList[i.FontID.Value].UsedInStaticText = true;
                        }
                    }
                }

                foreach (var text in DefineText2List)
                {
                    foreach (var i in text.TextRecords)
                    {
                        if (i.FontID is not null)
                        {
                            FontBaseList[i.FontID.Value].UsedInStaticText = true;
                        }
                    }
                }

                foreach (var item in CharacterList)
                {
                    switch (item)
                    {
                        case DefineBitsLosslessTag definebitslossless:
                            GlobalData.Characters[item.TagID] = new AptCharacterBitmap(definebitslossless, GlobalData);
                            break;
                        case DefineBitsLossless2Tag definebitslossless2:
                            GlobalData.Characters[item.TagID] = new AptCharacterBitmap(definebitslossless2, GlobalData);
                            break;
                        case JPEGTablesTag tables:
                            GlobalData.JPEGTables = tables.JPEGData;
                            break;
                        case DefineBitsTag definebits:
                            GlobalData.Characters[item.TagID] = new AptCharacterBitmap(definebits, GlobalData);
                            break;
                        case DefineBitsJPEG2Tag definebitsjpeg2:
                            GlobalData.Characters[item.TagID] = new AptCharacterBitmap(definebitsjpeg2, GlobalData);
                            break;
                        case DefineBitsJPEG3Tag definebitsjpeg3:
                            GlobalData.Characters[item.TagID] = new AptCharacterBitmap(definebitsjpeg3, GlobalData);
                            break;
                        case DefineButton2Tag definebutton2:
                            GlobalData.Characters[item.TagID] = new AptCharacterButton(definebutton2, GlobalData);
                            break;
                        case DefineFontTag definefont:
                            if (DefineFontInfoList.TryGetValue(item.TagID, out var fontinfo))
                            {
                                GlobalData.Characters[item.TagID] = new AptCharacterFont(definefont, fontinfo, GlobalData);
                            }
                            break;
                        case DefineFont2BaseTag definefont2:
                            GlobalData.Characters[item.TagID] = new AptCharacterFont(definefont2, GlobalData);
                            break;
                        case DefineMorphShapeTag definemorphshape:
                            GlobalData.Characters[item.TagID] = new AptCharacterMorph(definemorphshape, GlobalData);
                            break;
                        case DefineShapeTag defineshape:
                            GlobalData.Characters[item.TagID] = new AptCharacterShape(defineshape, GlobalData);
                            break;
                        case DefineShape2Tag defineshape2:
                            GlobalData.Characters[item.TagID] = new AptCharacterShape(defineshape2, GlobalData);
                            break;
                        case DefineShape3Tag defineshape3:
                            GlobalData.Characters[item.TagID] = new AptCharacterShape(defineshape3, GlobalData);
                            break;
                        case DefineSoundTag definesound:
                            GlobalData.Characters[item.TagID] = new AptCharacterSound(definesound, GlobalData);
                            break;
                        case DefineSpriteTag definesprite:
                            GlobalData.Characters[item.TagID] = new AptCharacterSprite(definesprite, GlobalData);
                            break;
                        case DefineTextTag definetext:
                            GlobalData.Characters[item.TagID] = new AptCharacterStaticText(definetext, GlobalData);
                            break;
                        case DefineText2Tag definetext2:
                            GlobalData.Characters[item.TagID] = new AptCharacterStaticText(definetext2, GlobalData);
                            break;
                        case DefineEditTextTag defineedittext:
                            GlobalData.Characters[item.TagID] = new AptCharacterText(defineedittext, GlobalData);
                            break;
                        case DefineVideoStreamTag definevideostream:
                            GlobalData.Characters[item.TagID] = new AptCharacterVideo(definevideostream, GlobalData);
                            break;
                    }
                }
                GlobalData.AllCharacters = new AptCharacter[GlobalData.Characters.Length + GlobalData.ExtraCharacters.Count];
                for (int i = 0; i < GlobalData.Characters.Length; i++)
                {
                    GlobalData.AllCharacters[i] = GlobalData.Characters[i];
                }
                for (int i = 0; i < GlobalData.ExtraCharacters.Count; i++)
                {
                    GlobalData.AllCharacters[GlobalData.Characters.Length + i] = GlobalData.ExtraCharacters[i];
                }
                GlobalData.movie = new AptMovie(swf.Tags, GlobalData);
                List<AptExport> exports = new();
                foreach (var e in ExportAssetsList)
                {
                    foreach (var s in e.Symbols)
                    {
                        exports.Add(new(s.SymbolID, s.SymbolName));
                        GlobalData.ReferencedCharacters[s.SymbolID] = true;
                    }
                }
                List<AptImport> imports = new();
                foreach (var imp in ImportAssetsList)
                {
                    for (int i = 0; i < imp.Tags.Count; i++)
                    {
                        imports.Add(new(imp.URL, imp.Names[i], imp.Tags[i]));
                    }
                }
                FindButtonHitTest();
                AptCharacterAnimation a;
                using FileStream outfile = new FileStream(basename + ".apt", FileMode.Create);
                {
                    GlobalData.output.curpass = 0;
                    string tag = "Apt Data:" + (char)(swf.FileInfo.Version + 48) + "4\u001A\0";
                    GlobalData.output.SetInitialValue(tag);
                    GlobalData.output.Align(0);
                    int chars = GlobalData.AllCharacters.Length;
                    foreach (var i in imports)
                    {
                        if (i.ID > chars)
                        {
                            chars = i.ID + 1;
                        }
                    }
                    a = new AptCharacterAnimation(GlobalData.movie, GlobalData, 0, swf.Header.FrameRate, swf.Header.FrameSize, chars, imports, exports);
                    GlobalData.AllCharacters[0] = a;
                    for (int i = 0; i < chars; i++)
                    {
                        switch (GlobalData.AllCharacters[i])
                        {
                            case AptCharacterSprite sprite:
                                sprite.movie.AddConstants();
                                break;
                            case AptCharacterAnimation animation:
                                animation.movie.AddConstants();
                                break;
                            case AptCharacterBitmap bitmap:
                                bitmaps.Add(bitmap);
                                break;
                            case AptCharacterButton button:
                                foreach (var b in button.Tag.Conditions)
                                {
                                    GlobalData.writer.AddActionConstants(b.Actions);
                                }
                                button.UpdateHitTestShape();
                                break;
                            case AptCharacterShape shape:
                                shape.UpdateShape(i);
                                shapes.Add(shape);
                                break;
                        }
                    }
                    a.WriteImportsExports();
                    GlobalData.MaxPasses = 5;
                    for (GlobalData.output.curpass = 1; GlobalData.output.curpass <= GlobalData.MaxPasses; GlobalData.output.curpass++)
                    {
                        GlobalData.output.Align(1);
                        if (GlobalData.output.curpass == 1)
                        {
                            a.constpointers[ConstPointerType.characters] = GlobalData.output.GetSize();
                        }
                        if (GlobalData.output.curpass == 3)
                        {
                            a.constpointers[ConstPointerType.maincharacter] = GlobalData.output.GetSize();
                        }
                        for (int i = 0; i < chars; i++)
                        {
                            var ch = GlobalData.AllCharacters[i];
                            if (ch is null)
                            {
                                GlobalData.output.Write(2, 0);
                                continue;
                            }
                            ch.OutputCharacter(i);
                        }
                    }
                    outfile.Write(GlobalData.output.GetBuffer());
                    GlobalData.output.curpass = 0;
                }
                using FileStream outfile2 = new FileStream(basename + ".const", FileMode.Create);
                {
                    GlobalData.output.SetInitialValue("Apt constant file\u001A\0");
                    GlobalData.MaxPasses = 1;
                    for (GlobalData.output.curpass = 1; GlobalData.output.curpass <= GlobalData.MaxPasses; GlobalData.output.curpass++)
                    {
                        GlobalData.output.Write(1, a.constpointers[ConstPointerType.maincharacter]);
                    }
                    GlobalData.writer.WriteConstTable();
                    outfile2.Write(GlobalData.output.GetBuffer());
                }
                PackTextures(basename);
                foreach (var s in shapes)
                {
                    ShapeIDs.Add(s.outid.ToString());
                    s.WriteShapeFile();
                }
                using FileStream outfile3 = new FileStream(basename + ".dat", FileMode.Create);
                {
                    using StreamWriter sr = new StreamWriter(outfile3);
                    {
                        sr.WriteLine("; Created by AptToXML.");
                        foreach (var s in NoPackedStrings)
                        {
                            sr.WriteLine(s);
                        }
                        sr.WriteLine("; Created by AptToXML.");
                        foreach (var s in PackedStrings)
                        {
                            sr.WriteLine(s);
                        }
                    }
                }
                using FileStream outfile4 = new FileStream(basename + ".xml", FileMode.Create);
                {
                    using StreamWriter sr = new StreamWriter(outfile4);
                    sr.WriteLine("<?xml version='1.0' encoding='utf-8'?>");
                    sr.WriteLine("<AssetDeclaration xmlns=\"uri:ea.com:eala:asset\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">");
                    sr.WriteLine("\t<AptAptData id=\"{0}_apt\" File=\"{1}.apt\" />", basename, basename);
                    sr.WriteLine("\t<AptConstData id=\"{0}_const\" File=\"{1}.const\" />", basename, basename);
                    sr.WriteLine("\t<AptDatData id=\"{0}_dat\" File=\"{1}.dat\" />", basename, basename);
                    ShapeIDs.Sort();
                    foreach (var id in ShapeIDs)
                    {
                        sr.WriteLine("\t<AptGeometryData id=\"{0}_{1}\" File=\"{2}_geometry\\{3}.ru\" AptID=\"{4}\"/>", basename, id, basename, id, id);
                    }
                    TextureIDs.Sort();
                    foreach (var id in TextureIDs)
                    {
                        sr.WriteLine("\t<Texture id=\"apt_{0}_{1}\" File=\"{2}\\apt_{3}_{4}.tga\" OutputFormat=\"A8R8G8B8\" GenerateMipMaps=\"false\" AllowAutomaticResize=\"false\"/>", basename, id, GlobalData.artdir, basename, id);
                    }
                    sr.WriteLine("</AssetDeclaration>");
                }
            }
        }
    }
}
