using SwfLib.Actions;
using SwfLib.Data;
using SwfLib.Filters;

namespace SwfLib.Buttons {
    public static class ButtonStreamExt {

        public static ButtonRecordEx ReadButtonRecordEx(this ISwfStreamReader reader) {
            var button = new ButtonRecordEx();
            button.States = (byte)reader.ReadByte();
            reader.Rewind(1);
            button.Reserved = (byte)reader.ReadUnsignedBits(2);
            var hasBlendMode = reader.ReadBit();
            var hasFilterList = reader.ReadBit();
            button.StateHitTest = reader.ReadBit();
            button.StateDown = reader.ReadBit();
            button.StateOver = reader.ReadBit();
            button.StateUp = reader.ReadBit();
            var isEnd = !hasBlendMode && !hasFilterList && button.IsEndButton;
            if (!isEnd) {
                button.CharacterID = reader.ReadUInt16();
                button.PlaceDepth = reader.ReadUInt16();
                button.PlaceMatrix = reader.ReadMatrix();
                button.ColorTransform = reader.ReadColorTransformRGBA();
                reader.AlignToByte();
                if (hasFilterList) {
                    reader.ReadFilterList(button.Filters);
                }
                if (hasBlendMode) {
                    button.BlendMode = (BlendMode)reader.ReadByte();
                }
            }
            return button;
        }

        public static ButtonCondition ReadButtonCondition(this ISwfStreamReader reader) {
            ushort c = reader.ReadUInt16();
            reader.Rewind(2);
            var res = new ButtonCondition {
                Conditions = c,
                IdleToOverDown = reader.ReadBit(),
                OutDownToIdle = reader.ReadBit(),
                OutDownToOverDown = reader.ReadBit(),
                OverDownToOutDown = reader.ReadBit(),
                OverDownToOverUp = reader.ReadBit(),
                OverUpToOverDown = reader.ReadBit(),
                OverUpToIdle = reader.ReadBit(),
                IdleToOverUp = reader.ReadBit(),
                KeyPress = (byte)reader.ReadUnsignedBits(7),
                OverDownToIdle = reader.ReadBit()
            };

            var ar = new ActionReader(reader);
            ActionBase action;
            do {
                action = ar.ReadAction();
                res.Actions.Add(action);
            } while (!(action is ActionEnd));
            for (int i = 0; i < res.Actions.Count; i++)
            {
                res.Actions[i].SetLabel(i, res.Actions);
            }
            return res;
        }
    }
}
