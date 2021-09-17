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
