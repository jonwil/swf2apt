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
