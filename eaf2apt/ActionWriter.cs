using SwfLib.Actions;
using System;
using System.Collections.Generic;

namespace eaf2apt
{
    class ActionWriter
    {
        Globals GlobalData;
        Dictionary<string, Dictionary<int, int>> bytepositions = new();
        Dictionary<string, Dictionary<string, int>> tracepositions = new();
        Dictionary<string, int> jumppositions = new();
        List<ActionPushItem> constants = new();
        Dictionary<string, int> constantrefs = new();
        string UniqueName(ActionBase action, int i, ActionPushItem item)
        {
            return @$"{action.GetHashCode()}_{i}_{item}";
        }
        public void AddActionConstants(List<ActionBase> actions)
        {
            for (int i = 0; i < actions.Count; i++)
            {
                int j = 0;
                var action = actions[i];
                switch (action)
                {
                    case ActionPush push:
                        foreach (var c in push.Items)
                        {
                            constants.Add(c);
                            constantrefs[UniqueName(action, j, c)] = constants.Count - 1;
                            j++;
                        }
                        break;
                    case ActionConstantPool constantpool:
                        foreach (var c in constantpool.ConstantPool)
                        {
                            constants.Add(c);
                            constantrefs[UniqueName(action, j, c)] = constants.Count - 1;
                            j++;
                        }
                        break;
                }
            }
        }
        public void WriteActions(int pass, string str, List<ActionBase> actions)
        {
            GlobalData.MaxPasses = Math.Max(GlobalData.MaxPasses, pass + 3);
            GlobalData.output.WriteFixup(pass, @$"{str}_Actions");
            GlobalData.output.Align(pass + 1);
            GlobalData.output.FixupPointer(pass + 1, @$"{str}_Actions");
            if (!bytepositions.ContainsKey(str))
            {
                bytepositions[str] = new();
            }
            if (!tracepositions.ContainsKey(str))
            {
                tracepositions[str] = new();
            }
            string withpos = "";
            int tracenum = 0;
            for (int i = 0; i < actions.Count; i++)
            {
                var action = actions[i];
                var tag = action.ActionCode;
                if (GlobalData.output.curpass == pass + 1)
                {
                    bytepositions[str][action.LocalLabel] = GlobalData.output.GetSize();
                }
                GlobalData.output.Write(pass + 1, (byte)tag);
                switch (action)
                {
                    case ActionConstantPool constantpool:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.Write(pass + 1, constantpool.ConstantPool.Count);
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_ConstantPool");
                            GlobalData.output.Align(pass + 2);
                            GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_ConstantPool");
                            if (GlobalData.output.curpass == pass + 2)
                            {
                                int c = 0;
                                foreach (var data in constantpool.ConstantPool)
                                {
                                    string u = UniqueName(action, c, data);
                                    GlobalData.output.Write(pass + 2, constantrefs[u]);
                                    c++;
                                }
                            }
                        }
                        break;
                    case ActionPush push:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.Write(pass + 1, push.Items.Count);
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_Items");
                            GlobalData.output.Align(pass + 2);
                            GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_Items");
                            if (GlobalData.output.curpass == pass + 2)
                            {
                                int c = 0;
                                foreach (var data in push.Items)
                                {
                                    string u = UniqueName(action, c, data);
                                    GlobalData.output.Write(pass + 2, constantrefs[u]);
                                    c++;
                                }
                            }
                        }
                        break;
                    case ActionJump jump:
                        {
                            if (GlobalData.output.curpass == pass + 1 || GlobalData.output.curpass == pass + 2)
                            {
                                int label = jump.BranchOffset;
                                if (GlobalData.output.curpass == pass + 2 && !bytepositions[str].ContainsKey(label))
                                {
                                    label = -1;
                                }
                                GlobalData.output.Align(pass + 1);
                                GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}");
                                if (GlobalData.output.curpass == pass + 1)
                                {
                                    jumppositions[@$"{str}_{action.GetHashCode()}"] = GlobalData.output.GetSize();
                                }
                                if (GlobalData.output.curpass == pass + 2)
                                {
                                    int delta = bytepositions[str][label] - jumppositions[@$"{str}_{action.GetHashCode()}"];
                                    GlobalData.output.FixupInt(pass + 2, @$"{str}_{action.GetHashCode()}", delta);
                                }
                            }
                        }
                        break;
                    case ActionIf iftrue:
                        {
                            if (GlobalData.output.curpass == pass + 1 || GlobalData.output.curpass == pass + 2)
                            {
                                int label = iftrue.BranchOffset;
                                if (GlobalData.output.curpass == pass + 2 && !bytepositions[str].ContainsKey(label))
                                {
                                    label = -1;
                                }
                                GlobalData.output.Align(pass + 1);
                                GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}");
                                if (GlobalData.output.curpass == pass + 1)
                                {
                                    jumppositions[@$"{str}_{action.GetHashCode()}"] = GlobalData.output.GetSize();
                                }
                                if (GlobalData.output.curpass == pass + 2)
                                {
                                    int delta = bytepositions[str][label] - jumppositions[@$"{str}_{action.GetHashCode()}"];
                                    GlobalData.output.FixupInt(pass + 2, @$"{str}_{action.GetHashCode()}", delta);
                                }
                            }
                        }
                        break;
                    case ActionIfFalse iffalse:
                        {
                            if (GlobalData.output.curpass == pass + 1 || GlobalData.output.curpass == pass + 2)
                            {
                                int label = iffalse.BranchOffset;
                                if (GlobalData.output.curpass == pass + 2 && !bytepositions[str].ContainsKey(label))
                                {
                                    label = -1;
                                }
                                GlobalData.output.Align(pass + 1);
                                GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}");
                                if (GlobalData.output.curpass == pass + 1)
                                {
                                    jumppositions[@$"{str}_{action.GetHashCode()}"] = GlobalData.output.GetSize();
                                }
                                if (GlobalData.output.curpass == pass + 2)
                                {
                                    int delta = bytepositions[str][label] - jumppositions[@$"{str}_{action.GetHashCode()}"];
                                    GlobalData.output.FixupInt(pass + 2, @$"{str}_{action.GetHashCode()}", delta);
                                }
                            }
                        }
                        break;
                    case ActionGotoFrame gotoframe:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.Write(pass + 1, (int)gotoframe.Frame);
                        }
                        break;
                    case ActionGotoFrame2 gotoframe2:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.Write(pass + 1, gotoframe2.Play);
                        }
                        break;
                    case ActionSetTarget settarget:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_TargetName");
                            GlobalData.output.Align(pass + 2);
                            GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_TargetName");
                            GlobalData.output.Write(pass + 2, settarget.TargetName);
                        }
                        break;
                    case ActionGoToLabel gotolabel:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_TargetName");
                            GlobalData.output.Align(pass + 2);
                            GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_TargetName");
                            GlobalData.output.Write(pass + 2, gotolabel.Label);
                        }
                        break;
                    case ActionGetURL geturl:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_UrlString");
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_TargetString");
                            GlobalData.output.Align(pass + 2);
                            GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_UrlString");
                            GlobalData.output.Write(pass + 2, geturl.UrlString);
                            GlobalData.output.Align(pass + 2);
                            GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_TargetString");
                            GlobalData.output.Write(pass + 2, geturl.TargetString);
                        }
                        break;
                    case ActionWith with:
                        {
                            GlobalData.output.Align(pass + 1);
                            withpos = @$"{str}_with_{action.GetHashCode()}";
                            if (GlobalData.output.curpass == pass + 1 || GlobalData.output.curpass == pass + 2)
                            {
                                int label = with.CodeSize;
                                GlobalData.output.WriteFixup(pass + 1, @$"{withpos}_skip");
                                if (GlobalData.output.curpass == pass + 1)
                                {
                                    jumppositions[@$"{withpos}_skip"] = GlobalData.output.GetSize();
                                }
                                if (GlobalData.output.curpass == pass + 2)
                                {
                                    int delta = bytepositions[str][label] - jumppositions[@$"{withpos}_skip"];
                                    GlobalData.output.FixupInt(pass + 2, @$"{withpos}_skip", delta);
                                }
                            }
                        }
                        break;
                    case ActionDefineFunction definefunction:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_Name");
                            GlobalData.output.Write(pass + 1, definefunction.Args.Count);
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_Args");
                            GlobalData.output.Align(pass + 2);
                            GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_Name");
                            GlobalData.output.Write(pass + 2, definefunction.Name);
                            GlobalData.output.Align(pass + 2);
                            GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_Args");
                            foreach (var p in definefunction.Args)
                            {
                                GlobalData.output.WriteFixup(pass + 2, @$"{str}_{action.GetHashCode()}_{p}");
                                GlobalData.output.Align(pass + 3);
                                GlobalData.output.FixupPointer(pass + 3, @$"{str}_{action.GetHashCode()}_{p}");
                                GlobalData.output.Write(pass + 3, p);
                            }
                            if (GlobalData.output.curpass == pass + 1 || GlobalData.output.curpass == pass + 2)
                            {
                                int label = definefunction.CodeSize;
                                GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}");
                                GlobalData.output.Align(pass + 1);
                                GlobalData.output.Write(pass + 1, 0x98765432);
                                GlobalData.output.Write(pass + 1, 0x12345678);
                                if (GlobalData.output.curpass == pass + 1)
                                {
                                    jumppositions[@$"{str}_{action.GetHashCode()}"] = GlobalData.output.GetSize();
                                }
                                if (GlobalData.output.curpass == pass + 2)
                                {
                                    int delta = bytepositions[str][label] - jumppositions[@$"{str}_{action.GetHashCode()}"];
                                    GlobalData.output.FixupInt(pass + 2, @$"{str}_{action.GetHashCode()}", delta);
                                }
                            }
                        }
                        break;
                    case ActionStoreRegister storeregister:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.Write(pass + 1, (int)storeregister.RegisterNumber);
                        }
                        break;
                    case ActionPushString pushstring:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_Value");
                            GlobalData.output.Align(pass + 2);
                            GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_Value");
                            GlobalData.output.Write(pass + 2, pushstring.Value);
                        }
                        break;
                    case ActionPushStringGetVariable pushstringgetvariable:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_Value");
                            GlobalData.output.Align(pass + 2);
                            GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_Value");
                            GlobalData.output.Write(pass + 2, pushstringgetvariable.Value);
                        }
                        break;
                    case ActionPushStringGetMember pushstringgetmember:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_Value");
                            GlobalData.output.Align(pass + 2);
                            GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_Value");
                            GlobalData.output.Write(pass + 2, pushstringgetmember.Value);
                        }
                        break;
                    case ActionPushStringSetVariable pushstringsetvariable:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_Value");
                            GlobalData.output.Align(pass + 2);
                            GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_Value");
                            GlobalData.output.Write(pass + 2, pushstringsetvariable.Value);
                        }
                        break;
                    case ActionPushStringSetMember pushstringsetmember:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_Value");
                            GlobalData.output.Align(pass + 2);
                            GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_Value");
                            GlobalData.output.Write(pass + 2, pushstringsetmember.Value);
                        }
                        break;
                    case ActionDictCallFuncAndPop dictcallfuncandpop:
                        {
                            GlobalData.output.Write(pass + 1, dictcallfuncandpop.Value);
                        }
                        break;
                    case ActionDictCallFuncSetVariable dictcallfuncsetvariable:
                        {
                            GlobalData.output.Write(pass + 1, dictcallfuncsetvariable.Value);
                        }
                        break;
                    case ActionDictCallMethodAndPop dictcallmethodandpop:
                        {
                            GlobalData.output.Write(pass + 1, dictcallmethodandpop.Value);
                        }
                        break;
                    case ActionDictCallMethodSetVariable dictcallmethodsetvariable:
                        {
                            GlobalData.output.Write(pass + 1, dictcallmethodsetvariable.Value);
                        }
                        break;
                    case ActionPushByte pushbyte:
                        {
                            GlobalData.output.Write(pass + 1, pushbyte.Value);
                        }
                        break;
                    case ActionPushRegister pushregister:
                        {
                            GlobalData.output.Write(pass + 1, pushregister.Value);
                        }
                        break;
                    case ActionStringDictByteGetVariable stringdictbytegetvariable:
                        {
                            GlobalData.output.Write(pass + 1, stringdictbytegetvariable.Value);
                        }
                        break;
                    case ActionStringDictByteGetMember stringdictbytegetmember:
                        {
                            GlobalData.output.Write(pass + 1, stringdictbytegetmember.Value);
                        }
                        break;
                    case ActionPushStringDictByte stringdictbyte:
                        {
                            GlobalData.output.Write(pass + 1, stringdictbyte.Value);
                        }
                        break;
                    case ActionPushWord pushword:
                        {
                            GlobalData.output.Write(pass + 1, pushword.Value);
                        }
                        break;
                    case ActionPushStringDictWord pushstringdictword:
                        {
                            GlobalData.output.Write(pass + 1, pushstringdictword.Value);
                        }
                        break;
                    case ActionPushDWord pushdword:
                        {
                            GlobalData.output.Write(pass + 1, pushdword.Value);
                        }
                        break;
                    case ActionPushFloat pushfloat:
                        {
                            GlobalData.output.Write(pass + 1, pushfloat.Value);
                        }
                        break;
                    case ActionTraceStart:
                        {
                            if (GlobalData.output.curpass == pass + 1 || GlobalData.output.curpass == pass + 2)
                            {
                                string label = @$"AfterTraceOffset{tracenum}";
                                if (GlobalData.output.curpass == pass + 2 && !tracepositions[str].ContainsKey(label))
                                {
                                    label = "AfterTraceOffset-1";
                                }
                                GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_tracestart_{tracenum}");
                                if (GlobalData.output.curpass == pass + 1)
                                {
                                    jumppositions[@$"{str}_{action.GetHashCode()}_tracestart_{tracenum}"] = GlobalData.output.GetSize();
                                }
                                if (GlobalData.output.curpass == pass + 2)
                                {
                                    int delta = tracepositions[str][label] - jumppositions[@$"{str}_{action.GetHashCode()}_tracestart_{tracenum}"];
                                    delta += 4;
                                    GlobalData.output.FixupInt(pass + 2, @$"{str}_{action.GetHashCode()}_tracestart_{tracenum}", delta);
                                }
                            }
                        }
                        break;
                    case ActionTrace:
                        {
                            string label = @$"AfterTraceOffset{tracenum}";
                            tracepositions[str][label] = GlobalData.output.GetSize();
                            tracenum++;
                        }
                        break;
                    case ActionTry trycatch:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_TrySize");
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_CatchSize");
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_FinallySize");
                            GlobalData.output.Write(pass + 1, trycatch.Flags);
                            GlobalData.output.Write(pass + 1, (byte)0);
                            GlobalData.output.Write(pass + 1, (byte)0);
                            if (trycatch.CatchInRegister)
                            {
                                GlobalData.output.Write(pass + 1, trycatch.CatchRegister);
                                GlobalData.output.Write(pass + 1, (byte)0);
                            }
                            else
                            {
                                GlobalData.output.Write(pass + 1, (byte)0);
                                GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_CatchName");
                                GlobalData.output.Align(pass + 2);
                                GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_CatchName");
                                GlobalData.output.Write(pass + 2, trycatch.CatchName);
                            }
                            if (GlobalData.output.curpass == pass + 1 || GlobalData.output.curpass == pass + 2)
                            {
                                int trylabel = trycatch.TrySize;
                                int catchlabel = trycatch.CatchSize;
                                int finallylabel = trycatch.CatchSize;
                                if (GlobalData.output.curpass == pass + 1)
                                {
                                    jumppositions[@$"{str}_{action.GetHashCode()}_try"] = GlobalData.output.GetSize();
                                }
                                if (GlobalData.output.curpass == pass + 2)
                                {
                                    int delta = bytepositions[str][trylabel] - jumppositions[@$"{str}_{action.GetHashCode()}_try"];
                                    GlobalData.output.FixupInt(pass + 2, @$"{str}_{action.GetHashCode()}_TrySize", delta);
                                    if (!trycatch.CatchBlock)
                                    {
                                        delta = 0;
                                    }
                                    else
                                    {
                                        delta = bytepositions[str][catchlabel] - bytepositions[str][trylabel];
                                    }
                                    GlobalData.output.FixupInt(pass + 2, @$"{str}_{action.GetHashCode()}_CatchSize", delta);
                                    if (!trycatch.FinallyBlock)
                                    {
                                        delta = 0;
                                    }
                                    else
                                    {
                                        delta = bytepositions[str][finallylabel] - bytepositions[str][catchlabel];
                                    }
                                    GlobalData.output.FixupInt(pass + 2, @$"{str}_{action.GetHashCode()}_FinallySize", delta);
                                }
                            }
                        }
                        break;
                    case ActionDefineFunction2 definefunction2:
                        {
                            GlobalData.output.Align(pass + 1);
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_Name");
                            GlobalData.output.Write(pass + 1, definefunction2.Parameters.Count);
                            GlobalData.output.Write(pass + 1, (ushort)definefunction2.RegisterCount);
                            GlobalData.output.Write(pass + 1, definefunction2.Flags);
                            GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}_Parameters");
                            GlobalData.output.Align(pass + 2);
                            GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_Name");
                            GlobalData.output.Write(pass + 2, definefunction2.Name);
                            GlobalData.output.Align(pass + 2);
                            GlobalData.output.FixupPointer(pass + 2, @$"{str}_{action.GetHashCode()}_Parameters");
                            foreach (var p in definefunction2.Parameters)
                            {
                                GlobalData.output.Write(pass + 2, (int)(byte)p.Register);
                                GlobalData.output.WriteFixup(pass + 2, @$"{str}_{action.GetHashCode()}_{p.GetHashCode()}_Name");
                                GlobalData.output.Align(pass + 3);
                                GlobalData.output.FixupPointer(pass + 3, @$"{str}_{action.GetHashCode()}_{p.GetHashCode()}_Name");
                                GlobalData.output.Write(pass + 3, p.Name);
                            }
                            if (GlobalData.output.curpass == pass + 1 || GlobalData.output.curpass == pass + 2)
                            {
                                int label = definefunction2.CodeSize;
                                if (GlobalData.output.curpass == pass + 2 && !bytepositions[str].ContainsKey(label))
                                {
                                    label = -1;
                                }
                                GlobalData.output.WriteFixup(pass + 1, @$"{str}_{action.GetHashCode()}");
                                GlobalData.output.Align(pass + 1);
                                GlobalData.output.Write(pass + 1, 0x98765432);
                                GlobalData.output.Write(pass + 1, 0x12345678);
                                if (GlobalData.output.curpass == pass + 1)
                                {
                                    jumppositions[@$"{str}_{action.GetHashCode()}"] = GlobalData.output.GetSize();
                                }
                                if (GlobalData.output.curpass == pass + 2)
                                {
                                    int delta = bytepositions[str][label] - jumppositions[@$"{str}_{action.GetHashCode()}"];
                                    GlobalData.output.FixupInt(pass + 2, @$"{str}_{action.GetHashCode()}", delta);
                                }
                            }
                        }
                        break;
                }
            }
            if (GlobalData.output.curpass == pass + 1)
            {
                bytepositions[str][-1] = GlobalData.output.GetSize();
                tracepositions[str]["AfterTraceOffset-1"] = GlobalData.output.GetSize();
            }
        }
        public void WriteConstTable()
        {
            for (GlobalData.output.curpass = 1; GlobalData.output.curpass <= 3; GlobalData.output.curpass++)
            {
                GlobalData.output.Write(1, constants.Count);
                GlobalData.output.WriteFixup(1, "Constants");
                GlobalData.output.Align(2);
                GlobalData.output.FixupPointer(2, "Constants");
                int index = 0;
                foreach (var c in constants)
                {
                    GlobalData.output.Align(2);
                    switch (c.Type)
                    {
                        case ActionPushItemType.String:
                            GlobalData.output.Write(2, (int)AptVirtualFunctionTable_Indices.AptVFT_StringValue);
                            GlobalData.output.WriteFixup(2, @$"{index}_String");
                            GlobalData.output.Align(3);
                            GlobalData.output.FixupPointer(3, @$"{index}_String");
                            GlobalData.output.Write(3, c.String);
                            break;
                        case ActionPushItemType.Double:
                            GlobalData.output.Write(2, (int)AptVirtualFunctionTable_Indices.AptVFT_Float);
                            GlobalData.output.Align(2);
                            GlobalData.output.Write(2, (float)c.Double);
                            break;
                        case ActionPushItemType.Integer:
                            GlobalData.output.Write(2, (int)AptVirtualFunctionTable_Indices.AptVFT_Integer);
                            GlobalData.output.Align(2);
                            GlobalData.output.Write(2, c.Integer);
                            break;
                        case ActionPushItemType.Constant8:
                            GlobalData.output.Write(2, (int)AptVirtualFunctionTable_Indices.AptVFT_Lookup);
                            GlobalData.output.Align(2);
                            GlobalData.output.Write(2, (int)c.Constant8);
                            break;
                        case ActionPushItemType.Constant16:
                            GlobalData.output.Write(2, (int)AptVirtualFunctionTable_Indices.AptVFT_Lookup);
                            GlobalData.output.Align(2);
                            GlobalData.output.Write(2, (int)c.Constant16);
                            break;
                        case ActionPushItemType.Float:
                            GlobalData.output.Write(2, (int)AptVirtualFunctionTable_Indices.AptVFT_Float);
                            GlobalData.output.Align(2);
                            GlobalData.output.Write(2, c.Float);
                            break;
                        case ActionPushItemType.Boolean:
                            GlobalData.output.Write(2, (int)AptVirtualFunctionTable_Indices.AptVFT_Boolean);
                            GlobalData.output.Align(2);
                            GlobalData.output.Write(2, (int)c.Boolean);
                            break;
                        case ActionPushItemType.Null:
                        case ActionPushItemType.Undefined:
                            GlobalData.output.Write(2, (int)AptVirtualFunctionTable_Indices.AptVFT_None);
                            GlobalData.output.Align(2);
                            GlobalData.output.Write(2, (int)c.Boolean);
                            break;
                        case ActionPushItemType.Register:
                            GlobalData.output.Write(2, (int)AptVirtualFunctionTable_Indices.AptVFT_Register);
                            GlobalData.output.Align(2);
                            GlobalData.output.Write(2, (int)c.Register);
                            break;
                    }
                    index++;
                }
            }
        }
        public ActionWriter(Globals g)
        {
            GlobalData = g;
        }
    }
}
