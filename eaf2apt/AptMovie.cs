using eaf2apt.Controls;
using SwfLib.Tags;
using SwfLib.Tags.ActionsTags;
using SwfLib.Tags.ControlTags;
using SwfLib.Tags.DisplayListTags;
using SwfLib.Tags.SoundTags;
using System;
using System.Collections.Generic;

namespace eaf2apt
{
    class AptMovie
    {
        Globals GlobalData;
        List<AptFrame> frames = new();
        public void AddConstants()
        {
            int framecount = frames.Count;
            if (framecount > 0)
            {
                for (int i = 0; i < framecount; i++)
                {
                    int controls = frames[i].Controls.Count;
                    if (controls > 0)
                    {
                        for (int j = 0; j < controls; j++)
                        {
                            var control = frames[i].Controls[j];
                            switch (control)
                            {
                                case AptControlPlaceObject2 placeobject2:
                                    if (placeobject2.Tag.HasClipActions)
                                    {
                                        foreach (var a in placeobject2.Tag.ClipActions.Records)
                                        {
                                            GlobalData.writer.AddActionConstants(a.Actions);
                                        }
                                    }
                                    break;
                                case AptControlDoAction doaction:
                                    GlobalData.writer.AddActionConstants(doaction.Tag.ActionRecords);
                                    break;
                                case AptControlDoInitAction doinitaction:
                                    GlobalData.writer.AddActionConstants(doinitaction.Tag.ActionRecords);
                                    break;
                            }
                        }
                    }
                }
            }
        }
        public void WriteMovieFrames()
        {
            GlobalData.MaxPasses = Math.Max(GlobalData.MaxPasses, 8);
            int famecount = frames.Count;
            GlobalData.output.Write(3, famecount);
            GlobalData.output.Align(3);
            if (famecount > 0)
            {
                GlobalData.output.WriteFixup(3, @$"{GetHashCode()}_Frames");
                GlobalData.output.Align(4);
                GlobalData.output.FixupPointer(4, @$"{GetHashCode()}_Frames");
                for (int i = 0; i < famecount; i++)
                {
                    frames[i].WriteFrame(i);
                }
            }
            else
            {
                GlobalData.output.Write(3, 0);
            }
            GlobalData.output.Write(3, 0);
        }
        public AptMovie(List<SwfTagBase> Tags, Globals globaldata)
        {
            int stream = 1;
            GlobalData = globaldata;
            AptFrame frame = new(globaldata);
            foreach (var Tag in Tags)
            {
                switch (Tag)
                {
                    case SetBackgroundColorTag color:
                        frame.Controls.Add(new AptControlBackgroundColor(color, globaldata));
                        break;
                    case DoActionTag doaction:
                        frame.Controls.Add(new AptControlDoAction(doaction, globaldata));
                        break;
                    case DoInitActionTag doinitaction:
                        frame.Controls.Add(new AptControlDoInitAction(doinitaction, globaldata));
                        break;
                    case FrameLabelTag label:
                        frame.Controls.Add(new AptControlFrameLabel(label, globaldata));
                        break;
                    case PlaceObject2Tag placeobject2:
                        frame.Controls.Add(new AptControlPlaceObject2(placeobject2, globaldata));
                        if (placeobject2.HasCharacter)
                        {
                            GlobalData.ReferencedCharacters[placeobject2.CharacterID] = true;
                        }
                        break;
                    case RemoveObject2Tag removeobject2:
                        frame.Controls.Add(new AptControlRemoveObject2(removeobject2, globaldata));
                        break;
                    case StartSoundTag startsound:
                        frame.Controls.Add(new AptControlStartSound(startsound, globaldata));
                        break;
                    case SoundStreamHeadTag soundstream:
                        frame.Controls.Add(new AptControlStartSoundStream(soundstream, stream, globaldata));
                        stream++;
                        break;
                    case ShowFrameTag:
                        frames.Add(frame);
                        frame = new(globaldata);
                        break;
                }
            }
        }
    }
}
