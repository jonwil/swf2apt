namespace eaf2apt
{
    class AptImport
    {
        public string URL;
        public string Name;
        public ushort ID;
        public AptImport(string url, string name, ushort id)
        {
            URL = url;
            Name = name;
            ID = id;
        }
    }
}
