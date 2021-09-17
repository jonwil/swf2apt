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
