/*
**	swf2apt
**	Copyright 2025 Jonathan Wilson
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

namespace eaf2apt
{
    public enum AptControlType
    {
        DoAction = 1,
        FrameLabel,
        PlaceObject2,
        RemoveObject2,
        BackgroundColour,
        StartSound,
        StartSoundStream,
        DoInitAction,
        PlaceObject3,
    }
    public enum AptCharacterType
    {
        Shape = 1,
        Text,
        Font,
        Button,
        Sprite,
        Sound,
        Bitmap,
        Morph,
        Animation,
        StaticText,
        None,
        Video,
        Level = 15,
        CustomControl,
        Max,
    }
    public enum AptVirtualFunctionTable_Indices
    {
        AptVFT_xxx,
        AptVFT_StringValue,
        AptVFT_Property,
        AptVFT_None,
        AptVFT_Register,
        AptVFT_Boolean,
        AptVFT_Float,
        AptVFT_Integer,
        AptVFT_Lookup,
        AptVFT_NativeFunction,
        AptVFT_FrameStack,
        AptVFT_Extern,
        AptVFT_CharacterInstHandle,
        AptVFT_Sound,
        AptVFT_Array,
        AptVFT_Math,
        AptVFT_Key,
        AptVFT_Global,
        AptVFT_ScriptColour,
        AptVFT_Object,
        AptVFT_Prototype,
        AptVFT_Date,
        AptVFT_MovieClip,
        AptVFT_Mouse,
        AptVFT_XmlNode,
        AptVFT_Xml,
        AptVFT_XmlAttributes,
        AptVFT_LoadVars,
        AptVFT_TextFormat,
        AptVFT_Extension,
        AptVFT_GlobalExtension,
        AptVFT_Stage,
        AptVFT_Error,
        AptVFT_StringObject,
        AptVFT_ScriptFunction1,
        AptVFT_ScriptFunction2,
        AptVFT_ScriptFunctionByteCodeBlock,
        AptVFT_CIHNone,
        AptVFT_NumVFTs,
    }
    unsafe struct AptFloatArrayCXForm
    {
        public fixed float scale[4];
        public fixed float translate[4];
    };
    struct AptRect
    {
        public float fLeft;
        public float fTop;
        public float fRight;
        public float fBottom;
    };
    struct AptCharacterGlyphEntry
    {
        public short nIndex;
        public short nAdvance;
    };
}
