using System;
using System.Collections.Generic;
using System.IO;

namespace SwfLib.Actions {
    public class ActionReader : IActionVisitor<ushort, ActionBase> {

        private readonly ISwfStreamReader _reader;
        private readonly ActionsFactory _factory;

        public ActionReader(ISwfStreamReader reader) {
            _reader = reader;
            _factory = new ActionsFactory();
        }

        public ActionBase ReadAction() {
            int pos = (int)_reader.Position;
            var code = (ActionCode)_reader.ReadByte();
            ushort length = (byte)code >= 0x80 ? _reader.ReadUInt16() : (ushort)0;
            var action = _factory.Create(code);
            action.LocalLabel = pos;
            action.AcceptVisitor(this, length);
            return action;
        }

        #region SWF 3

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionGotoFrame action, ushort length) {
            action.Frame = _reader.ReadUInt16();
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionGetURL action, ushort length) {
            action.UrlString = _reader.ReadString();
            action.TargetString = _reader.ReadString();
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionNextFrame action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPreviousFrame action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPlay action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionStop action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionToggleQuality action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionStopSounds action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionWaitForFrame action, ushort length) {
            action.Frame = _reader.ReadUInt16();
            action.SkipCount = _reader.ReadByte();
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionSetTarget action, ushort length) {
            action.TargetName = _reader.ReadString();
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionGoToLabel action, ushort length) {
            action.Label = _reader.ReadString();
            return action;
        }

        #endregion

        #region SWF 4

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionAdd action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionDivide action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionMultiply action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionSubtract action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionEquals action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionLess action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionAnd action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionNot action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionOr action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionStringAdd action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionStringEquals action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionStringExtract action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionStringLength action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionMBStringExtract action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionMBStringLength action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionStringLess action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPop action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPush action, ushort length) {
            var position = _reader.Position;
            while (_reader.Position - position < length) {
                var item = new ActionPushItem();
                var type = (ActionPushItemType)_reader.ReadByte();
                item.Type = type;
                switch (type) {
                    case ActionPushItemType.String:
                        item.String = _reader.ReadString();
                        break;
                    case ActionPushItemType.Float:
                        item.Float = _reader.ReadSingle();
                        break;
                    case ActionPushItemType.Null:
                        break;
                    case ActionPushItemType.Undefined:
                        break;
                    case ActionPushItemType.Register:
                        item.Register = _reader.ReadByte();
                        break;
                    case ActionPushItemType.Boolean:
                        item.Boolean = _reader.ReadByte();
                        break;
                    case ActionPushItemType.Double:
                        item.Double = _reader.ReadDouble();
                        break;
                    case ActionPushItemType.Integer:
                        item.Integer = _reader.ReadInt32();
                        break;
                    case ActionPushItemType.Constant8:
                        item.Constant8 = _reader.ReadByte();
                        break;
                    case ActionPushItemType.Constant16:
                        item.Constant16 = _reader.ReadUInt16();
                        break;
                    default:
                        throw new NotSupportedException("Unknown PushData type " + type);
                }
                action.Items.Add(item);
            }
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionAsciiToChar action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionCharToAscii action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionToInteger action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionMBAsciiToChar action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionMBCharToAscii action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionCall action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionIf action, ushort length) {
            action.BranchOffset = _reader.ReadSInt16();
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionJump action, ushort length) {
            action.BranchOffset = _reader.ReadSInt16();
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionGetVariable action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionSetVariable action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionGetURL2 action, ushort length) {
            action.Flags = _reader.ReadByte();
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionGetProperty action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionGotoFrame2 action, ushort length) {
            action.Reserved = (byte)_reader.ReadUnsignedBits(6);
            var hasBias = _reader.ReadBit();
            action.Play = _reader.ReadBit();
            if (hasBias) {
                action.SceneBias = _reader.ReadUInt16();
            }
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionRemoveSprite action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionSetProperty action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionSetTarget2 action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionStartDrag action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionWaitForFrame2 action, ushort length) {
            action.SkipCount = _reader.ReadByte();
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionCloneSprite action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionEndDrag action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionGetTime action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionRandomNumber action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionTrace action, ushort length) {
            return action;
        }

        #endregion

        #region SWF 5

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionCallFunction action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionCallMethod action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionConstantPool action, ushort length) {
            ushort count = _reader.ReadUInt16();
            for (var i = 0; i < count; i++) {
                ActionPushItem item = new();
                item.Type = ActionPushItemType.String;
                item.String = _reader.ReadString();
                action.ConstantPool.Add(item);
            }
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionDefineFunction action, ushort length) {
            action.Name = _reader.ReadString();
            var args = _reader.ReadUInt16();
            for (var i = 0; i < args; i++) {
                action.Args.Add(_reader.ReadString());
            }
            action.CodeSize = _reader.ReadUInt16();
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionDefineLocal action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionDefineLocal2 action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionDelete action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionDelete2 action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionEnumerate action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionEquals2 action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionGetMember action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionInitArray action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionInitObject action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionNewMethod action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionNewObject action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionSetMember action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionTargetPath action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionWith action, ushort arg) {
            action.CodeSize = _reader.ReadUInt16();
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionToNumber action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionToString action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionTypeOf action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionAdd2 action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionLess2 action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionModulo action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionBitAnd action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionBitLShift action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionBitOr action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionBitRShift action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionBitURShift action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionBitXor action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionDecrement action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionIncrement action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushDuplicate action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionReturn action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionStackSwap action, ushort arg) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionStoreRegister action, ushort arg) {
            action.RegisterNumber = _reader.ReadByte();
            return action;
        }

        #endregion

        #region SWF 6

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionInstanceOf action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionEnumerate2 action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionStrictEquals action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionGreater action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionStringGreater action, ushort length) {
            return action;
        }

        #endregion

        #region SWF 7

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionDefineFunction2 action, ushort length) {
            action.Name = _reader.ReadString();
            var args = _reader.ReadUInt16();
            action.RegisterCount = _reader.ReadByte();
            action.Flags = _reader.ReadUInt16();
            _reader.Rewind(2);
            action.PreloadParent = _reader.ReadBit();
            action.PreloadRoot = _reader.ReadBit();
            action.SuppressSuper = _reader.ReadBit();
            action.PreloadSuper = _reader.ReadBit();
            action.SuppressArguments = _reader.ReadBit();
            action.PreloadArguments = _reader.ReadBit();
            action.SuppressThis = _reader.ReadBit();
            action.PreloadThis = _reader.ReadBit();
            action.Reserved = (byte)_reader.ReadUnsignedBits(7);
            action.PreloadGlobal = _reader.ReadBit();

            for (var i = 0; i < args; i++) {
                action.Parameters.Add(new RegisterParam {
                    Register = _reader.ReadByte(),
                    Name = _reader.ReadString()
                });
            }
            action.CodeSize = _reader.ReadUInt16();
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionExtends action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionCastOp action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionImplementsOp action, ushort length) {
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionTry action, ushort length) {
            action.Flags = _reader.ReadByte();
            _reader.Rewind(1);
            action.Reserved = (byte)_reader.ReadUnsignedBits(5);
            action.CatchInRegister = _reader.ReadBit();
            action.FinallyBlock = _reader.ReadBit();
            action.CatchBlock = _reader.ReadBit();
            action.TrySize = _reader.ReadUInt16();
            action.CatchSize = _reader.ReadUInt16();
            action.FinallySize = _reader.ReadUInt16();
            if (action.CatchInRegister) {
                action.CatchRegister = _reader.ReadByte();
            } else {
                action.CatchName = _reader.ReadString();
            }
            return action;
        }

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionThrow action, ushort length) {
            return new ActionThrow();
        }

        public ActionBase Visit(ActionEnd action, ushort arg) {
            return action;
        }

        #endregion

        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushThis action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushGlobal action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushZero action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushOne action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionCallFuncAndPop action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionCallFuncSetVariable action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionCallMethodAndPop action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionCallMethodSetVariable action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushThisVariable action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushGlobalVariable action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushZeroSetVar action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushTrue action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushFalse action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushNULL action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushUndefined action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionTraceStart action, ushort length) {
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushString action, ushort length) {
            action.Value = _reader.ReadString();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushStringDictByte action, ushort length) {
            action.Value = _reader.ReadByte();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushStringDictWord action, ushort length) {
            action.Value = _reader.ReadUInt16();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushStringGetVariable action, ushort length) {
            action.Value = _reader.ReadString();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushStringGetMember action, ushort length) {
            action.Value = _reader.ReadString();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushStringSetVariable action, ushort length) {
            action.Value = _reader.ReadString();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushStringSetMember action, ushort length) {
            action.Value = _reader.ReadString();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionStringDictByteGetVariable action, ushort length) {
            action.Value = _reader.ReadByte();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionStringDictByteGetMember action, ushort length) {
            action.Value = _reader.ReadByte();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionDictCallFuncAndPop action, ushort length) {
            action.Value = _reader.ReadByte();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionDictCallFuncSetVariable action, ushort length) {
            action.Value = _reader.ReadByte();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionDictCallMethodAndPop action, ushort length) {
            action.Value = _reader.ReadByte();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionDictCallMethodSetVariable action, ushort length) {
            action.Value = _reader.ReadByte();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushFloat action, ushort length) {
            action.Value = _reader.ReadSingle();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushByte action, ushort length) {
            action.Value = _reader.ReadByte();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushWord action, ushort length) {
            action.Value = _reader.ReadUInt16();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushDWord action, ushort length) {
            action.Value = _reader.ReadUInt32();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionIfFalse action, ushort length) {
            action.BranchOffset = _reader.ReadSInt16();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionPushRegister action, ushort length) {
            action.Value = _reader.ReadByte();
            return action;
        }
        ActionBase IActionVisitor<ushort, ActionBase>.Visit(ActionUnknown action, ushort length) {
            action.Data = _reader.ReadBytes(length);
            return action;
        }
    }
}
