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

using SwfLib.Tags.SoundTags;
using System.Diagnostics;
using System.IO;

namespace eaf2apt.Characters
{
    class AptCharacterSound : AptCharacter
    {
        public override void OutputCharacter(int i)
        {
            base.OutputCharacter(i);
            GlobalData.output.Write(3, (int)AptCharacterType.Sound);
            GlobalData.output.Write(3, 0x09876543);

            if (GlobalData.IsTT)
            {
                GlobalData.output.Write(3, 0x0);
                GlobalData.output.Write(3, 0x0);
            }

            GlobalData.output.Write(3, i);
        }
        public AptCharacterSound(DefineSoundTag tag, Globals globaldata) : base(globaldata, tag.TagID)
        {
            if (tag.SoundFormat == 2)
            {
                string name = @$"{globaldata.soundsdir}\{tag.TagID}.mp3";
                FileStream stream = new FileStream(name, FileMode.CreateNew);
                stream.Write(tag.SoundData, 0, tag.SoundData.Length);
                stream.Close();
                string wavname = @$"{globaldata.soundsdir}\{tag.TagID}.wav";
                var process = Process.Start("madplay", $@"-Q {name} --output=wave:{wavname}");
                process.WaitForExit();
                File.Delete(name);
            }
        }
    }
}
