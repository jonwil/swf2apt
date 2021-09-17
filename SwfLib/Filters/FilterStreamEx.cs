using System.Collections.Generic;

namespace SwfLib.Filters {
    public static class FilterStreamEx {

        private static readonly FilterReader _reader = new FilterReader();
        public static void ReadFilterList(this ISwfStreamReader reader, List<BaseFilter> target) {
            var count = reader.ReadByte();
            for (var i = 0; i < count; i++) {
                var filter = reader.ReadFilter();
                target.Add(filter);
            }
        }

        public static BaseFilter ReadFilter(this ISwfStreamReader reader) {
            return _reader.Read(reader);
        }
    }
}
