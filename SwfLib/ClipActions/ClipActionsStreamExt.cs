using System.Collections.Generic;
using System.IO;
using SwfLib.Actions;

namespace SwfLib.ClipActions {
    public static class ClipActionsStreamExt {

        public static void ReadClipActions(this ISwfStreamReader reader, byte swfVersion, ClipActionsList clipActions) {
            clipActions.Reserved = reader.ReadUInt16();
            clipActions.Flags = reader.ReadClipEventFlags(swfVersion);
            reader.ReadClipActionRecords(swfVersion, clipActions.Records);

        }

        public static void ReadClipActionRecords(this ISwfStreamReader reader, byte swfVersion, List<ClipActionRecord> target) {
            ClipActionRecord record;
            do {
                record = reader.ReadClipActionRecord(swfVersion);
                if (!record.EventFlags.IsEmpty)
                {
                    target.Add(record);
                }
            } while (!record.EventFlags.IsEmpty);
        }

        public static ClipActionRecord ReadClipActionRecord(this ISwfStreamReader reader, byte swfVersion) {
            var record = new ClipActionRecord();
            if (swfVersion >= 6)
            {
                record.Flags = reader.ReadUInt32();
                reader.Rewind(4);
            }
            else
            {
                record.Flags = reader.ReadUInt16();
                reader.Rewind(2);
            }
            record.EventFlags = reader.ReadClipEventFlags(swfVersion);
            if (record.EventFlags.IsEmpty) return record;

            var offset = reader.ReadUInt32();
            if (record.EventFlags.ClipEventKeyPress) {
                record.KeyCode = reader.ReadByte();
            } else {
                record.KeyCode = 0;
            }

            ActionBase action;
            var ar = new ActionReader(reader);
            do {
                action = ar.ReadAction();
                record.Actions.Add(action);
            } while (!(action is ActionEnd));
            for (int i = 0; i < record.Actions.Count; i++)
            {
                record.Actions[i].SetLabel(i, record.Actions);
            }
            return record;
        }

        public static ClipEventFlags ReadClipEventFlags(this ISwfStreamReader reader, byte swfVersion) {
            var res = new ClipEventFlags {
                ClipEventKeyUp = reader.ReadBit(),
                ClipEventKeyDown = reader.ReadBit(),
                ClipEventMouseUp = reader.ReadBit(),
                ClipEventMouseDown = reader.ReadBit(),
                ClipEventMouseMove = reader.ReadBit(),
                ClipEventUnload = reader.ReadBit(),
                ClipEventEnterFrame = reader.ReadBit(),
                ClipEventLoad = reader.ReadBit(),

                ClipEventDragOver = reader.ReadBit(),
                ClipEventRollOut = reader.ReadBit(),
                ClipEventRollOver = reader.ReadBit(),
                ClipEventReleaseOutside = reader.ReadBit(),
                ClipEventRelease = reader.ReadBit(),
                ClipEventPress = reader.ReadBit(),
                ClipEventInitialize = reader.ReadBit(),
                ClipEventData = reader.ReadBit(),
            };

            if (swfVersion >= 6) {
                res.Reserved = (byte)reader.ReadUnsignedBits(5);
                res.ClipEventConstruct = reader.ReadBit();
                res.ClipEventKeyPress = reader.ReadBit();
                res.ClipEventDragOut = reader.ReadBit();

                res.Reserved2 = reader.ReadByte();
            }
            return res;
        }
    }
}
