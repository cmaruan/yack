#include "x86.h"
# TRAP
.globl alltraps
alltraps:
	# Build trap frame.
  pushl %ds
  pushl %es
  pushl %fs
  pushl %gs
  pushal
  
  # Set up data segments.
  movw $(X86_GDT_SEG_DATAK<<3), %ax
  movw %ax, %ds
  movw %ax, %es

  # Call trap(tf), where tf=%esp
  pushl %esp
  call trap_handler
  addl $4, %esp

  # Return falls through to trapret...
.globl trapret
trapret:
  popal
  popl %gs
  popl %fs
  popl %es
  popl %ds
  addl $0x8, %esp  # trapno and errcode
  iret  



# handlers
.globl trap_handler_0
trap_handler_0:
  pushl $0
  pushl $0
  jmp alltraps
.globl trap_handler_1
trap_handler_1:
  pushl $0
  pushl $1
  jmp alltraps
.globl trap_handler_2
trap_handler_2:
  pushl $0
  pushl $2
  jmp alltraps
.globl trap_handler_3
trap_handler_3:
  pushl $0
  pushl $3
  jmp alltraps
.globl trap_handler_4
trap_handler_4:
  pushl $0
  pushl $4
  jmp alltraps
.globl trap_handler_5
trap_handler_5:
  pushl $0
  pushl $5
  jmp alltraps
.globl trap_handler_6
trap_handler_6:
  pushl $0
  pushl $6
  jmp alltraps
.globl trap_handler_7
trap_handler_7:
  pushl $0
  pushl $7
  jmp alltraps
.globl trap_handler_8
trap_handler_8:
  pushl $8
  jmp alltraps
.globl trap_handler_9
trap_handler_9:
  pushl $0
  pushl $9
  jmp alltraps
.globl trap_handler_10
trap_handler_10:
  pushl $10
  jmp alltraps
.globl trap_handler_11
trap_handler_11:
  pushl $11
  jmp alltraps
.globl trap_handler_12
trap_handler_12:
  pushl $12
  jmp alltraps
.globl trap_handler_13
trap_handler_13:
  pushl $13
  jmp alltraps
.globl trap_handler_14
trap_handler_14:
  pushl $14
  jmp alltraps
.globl trap_handler_15
trap_handler_15:
  pushl $0
  pushl $15
  jmp alltraps
.globl trap_handler_16
trap_handler_16:
  pushl $0
  pushl $16
  jmp alltraps
.globl trap_handler_17
trap_handler_17:
  pushl $17
  jmp alltraps
.globl trap_handler_18
trap_handler_18:
  pushl $0
  pushl $18
  jmp alltraps
.globl trap_handler_19
trap_handler_19:
  pushl $0
  pushl $19
  jmp alltraps
.globl trap_handler_20
trap_handler_20:
  pushl $0
  pushl $20
  jmp alltraps
.globl trap_handler_21
trap_handler_21:
  pushl $0
  pushl $21
  jmp alltraps
.globl trap_handler_22
trap_handler_22:
  pushl $0
  pushl $22
  jmp alltraps
.globl trap_handler_23
trap_handler_23:
  pushl $0
  pushl $23
  jmp alltraps
.globl trap_handler_24
trap_handler_24:
  pushl $0
  pushl $24
  jmp alltraps
.globl trap_handler_25
trap_handler_25:
  pushl $0
  pushl $25
  jmp alltraps
.globl trap_handler_26
trap_handler_26:
  pushl $0
  pushl $26
  jmp alltraps
.globl trap_handler_27
trap_handler_27:
  pushl $0
  pushl $27
  jmp alltraps
.globl trap_handler_28
trap_handler_28:
  pushl $0
  pushl $28
  jmp alltraps
.globl trap_handler_29
trap_handler_29:
  pushl $0
  pushl $29
  jmp alltraps
.globl trap_handler_30
trap_handler_30:
  pushl $0
  pushl $30
  jmp alltraps
.globl trap_handler_31
trap_handler_31:
  pushl $0
  pushl $31
  jmp alltraps
.globl trap_handler_32
trap_handler_32:
  pushl $0
  pushl $32
  jmp alltraps
.globl trap_handler_33
trap_handler_33:
  pushl $0
  pushl $33
  jmp alltraps
.globl trap_handler_34
trap_handler_34:
  pushl $0
  pushl $34
  jmp alltraps
.globl trap_handler_35
trap_handler_35:
  pushl $0
  pushl $35
  jmp alltraps
.globl trap_handler_36
trap_handler_36:
  pushl $0
  pushl $36
  jmp alltraps
.globl trap_handler_37
trap_handler_37:
  pushl $0
  pushl $37
  jmp alltraps
.globl trap_handler_38
trap_handler_38:
  pushl $0
  pushl $38
  jmp alltraps
.globl trap_handler_39
trap_handler_39:
  pushl $0
  pushl $39
  jmp alltraps
.globl trap_handler_40
trap_handler_40:
  pushl $0
  pushl $40
  jmp alltraps
.globl trap_handler_41
trap_handler_41:
  pushl $0
  pushl $41
  jmp alltraps
.globl trap_handler_42
trap_handler_42:
  pushl $0
  pushl $42
  jmp alltraps
.globl trap_handler_43
trap_handler_43:
  pushl $0
  pushl $43
  jmp alltraps
.globl trap_handler_44
trap_handler_44:
  pushl $0
  pushl $44
  jmp alltraps
.globl trap_handler_45
trap_handler_45:
  pushl $0
  pushl $45
  jmp alltraps
.globl trap_handler_46
trap_handler_46:
  pushl $0
  pushl $46
  jmp alltraps
.globl trap_handler_47
trap_handler_47:
  pushl $0
  pushl $47
  jmp alltraps
.globl trap_handler_48
trap_handler_48:
  pushl $0
  pushl $48
  jmp alltraps
.globl trap_handler_49
trap_handler_49:
  pushl $0
  pushl $49
  jmp alltraps
.globl trap_handler_50
trap_handler_50:
  pushl $0
  pushl $50
  jmp alltraps
.globl trap_handler_51
trap_handler_51:
  pushl $0
  pushl $51
  jmp alltraps
.globl trap_handler_52
trap_handler_52:
  pushl $0
  pushl $52
  jmp alltraps
.globl trap_handler_53
trap_handler_53:
  pushl $0
  pushl $53
  jmp alltraps
.globl trap_handler_54
trap_handler_54:
  pushl $0
  pushl $54
  jmp alltraps
.globl trap_handler_55
trap_handler_55:
  pushl $0
  pushl $55
  jmp alltraps
.globl trap_handler_56
trap_handler_56:
  pushl $0
  pushl $56
  jmp alltraps
.globl trap_handler_57
trap_handler_57:
  pushl $0
  pushl $57
  jmp alltraps
.globl trap_handler_58
trap_handler_58:
  pushl $0
  pushl $58
  jmp alltraps
.globl trap_handler_59
trap_handler_59:
  pushl $0
  pushl $59
  jmp alltraps
.globl trap_handler_60
trap_handler_60:
  pushl $0
  pushl $60
  jmp alltraps
.globl trap_handler_61
trap_handler_61:
  pushl $0
  pushl $61
  jmp alltraps
.globl trap_handler_62
trap_handler_62:
  pushl $0
  pushl $62
  jmp alltraps
.globl trap_handler_63
trap_handler_63:
  pushl $0
  pushl $63
  jmp alltraps
.globl trap_handler_64
trap_handler_64:
  pushl $0
  pushl $64
  jmp alltraps
.globl trap_handler_65
trap_handler_65:
  pushl $0
  pushl $65
  jmp alltraps
.globl trap_handler_66
trap_handler_66:
  pushl $0
  pushl $66
  jmp alltraps
.globl trap_handler_67
trap_handler_67:
  pushl $0
  pushl $67
  jmp alltraps
.globl trap_handler_68
trap_handler_68:
  pushl $0
  pushl $68
  jmp alltraps
.globl trap_handler_69
trap_handler_69:
  pushl $0
  pushl $69
  jmp alltraps
.globl trap_handler_70
trap_handler_70:
  pushl $0
  pushl $70
  jmp alltraps
.globl trap_handler_71
trap_handler_71:
  pushl $0
  pushl $71
  jmp alltraps
.globl trap_handler_72
trap_handler_72:
  pushl $0
  pushl $72
  jmp alltraps
.globl trap_handler_73
trap_handler_73:
  pushl $0
  pushl $73
  jmp alltraps
.globl trap_handler_74
trap_handler_74:
  pushl $0
  pushl $74
  jmp alltraps
.globl trap_handler_75
trap_handler_75:
  pushl $0
  pushl $75
  jmp alltraps
.globl trap_handler_76
trap_handler_76:
  pushl $0
  pushl $76
  jmp alltraps
.globl trap_handler_77
trap_handler_77:
  pushl $0
  pushl $77
  jmp alltraps
.globl trap_handler_78
trap_handler_78:
  pushl $0
  pushl $78
  jmp alltraps
.globl trap_handler_79
trap_handler_79:
  pushl $0
  pushl $79
  jmp alltraps
.globl trap_handler_80
trap_handler_80:
  pushl $0
  pushl $80
  jmp alltraps
.globl trap_handler_81
trap_handler_81:
  pushl $0
  pushl $81
  jmp alltraps
.globl trap_handler_82
trap_handler_82:
  pushl $0
  pushl $82
  jmp alltraps
.globl trap_handler_83
trap_handler_83:
  pushl $0
  pushl $83
  jmp alltraps
.globl trap_handler_84
trap_handler_84:
  pushl $0
  pushl $84
  jmp alltraps
.globl trap_handler_85
trap_handler_85:
  pushl $0
  pushl $85
  jmp alltraps
.globl trap_handler_86
trap_handler_86:
  pushl $0
  pushl $86
  jmp alltraps
.globl trap_handler_87
trap_handler_87:
  pushl $0
  pushl $87
  jmp alltraps
.globl trap_handler_88
trap_handler_88:
  pushl $0
  pushl $88
  jmp alltraps
.globl trap_handler_89
trap_handler_89:
  pushl $0
  pushl $89
  jmp alltraps
.globl trap_handler_90
trap_handler_90:
  pushl $0
  pushl $90
  jmp alltraps
.globl trap_handler_91
trap_handler_91:
  pushl $0
  pushl $91
  jmp alltraps
.globl trap_handler_92
trap_handler_92:
  pushl $0
  pushl $92
  jmp alltraps
.globl trap_handler_93
trap_handler_93:
  pushl $0
  pushl $93
  jmp alltraps
.globl trap_handler_94
trap_handler_94:
  pushl $0
  pushl $94
  jmp alltraps
.globl trap_handler_95
trap_handler_95:
  pushl $0
  pushl $95
  jmp alltraps
.globl trap_handler_96
trap_handler_96:
  pushl $0
  pushl $96
  jmp alltraps
.globl trap_handler_97
trap_handler_97:
  pushl $0
  pushl $97
  jmp alltraps
.globl trap_handler_98
trap_handler_98:
  pushl $0
  pushl $98
  jmp alltraps
.globl trap_handler_99
trap_handler_99:
  pushl $0
  pushl $99
  jmp alltraps
.globl trap_handler_100
trap_handler_100:
  pushl $0
  pushl $100
  jmp alltraps
.globl trap_handler_101
trap_handler_101:
  pushl $0
  pushl $101
  jmp alltraps
.globl trap_handler_102
trap_handler_102:
  pushl $0
  pushl $102
  jmp alltraps
.globl trap_handler_103
trap_handler_103:
  pushl $0
  pushl $103
  jmp alltraps
.globl trap_handler_104
trap_handler_104:
  pushl $0
  pushl $104
  jmp alltraps
.globl trap_handler_105
trap_handler_105:
  pushl $0
  pushl $105
  jmp alltraps
.globl trap_handler_106
trap_handler_106:
  pushl $0
  pushl $106
  jmp alltraps
.globl trap_handler_107
trap_handler_107:
  pushl $0
  pushl $107
  jmp alltraps
.globl trap_handler_108
trap_handler_108:
  pushl $0
  pushl $108
  jmp alltraps
.globl trap_handler_109
trap_handler_109:
  pushl $0
  pushl $109
  jmp alltraps
.globl trap_handler_110
trap_handler_110:
  pushl $0
  pushl $110
  jmp alltraps
.globl trap_handler_111
trap_handler_111:
  pushl $0
  pushl $111
  jmp alltraps
.globl trap_handler_112
trap_handler_112:
  pushl $0
  pushl $112
  jmp alltraps
.globl trap_handler_113
trap_handler_113:
  pushl $0
  pushl $113
  jmp alltraps
.globl trap_handler_114
trap_handler_114:
  pushl $0
  pushl $114
  jmp alltraps
.globl trap_handler_115
trap_handler_115:
  pushl $0
  pushl $115
  jmp alltraps
.globl trap_handler_116
trap_handler_116:
  pushl $0
  pushl $116
  jmp alltraps
.globl trap_handler_117
trap_handler_117:
  pushl $0
  pushl $117
  jmp alltraps
.globl trap_handler_118
trap_handler_118:
  pushl $0
  pushl $118
  jmp alltraps
.globl trap_handler_119
trap_handler_119:
  pushl $0
  pushl $119
  jmp alltraps
.globl trap_handler_120
trap_handler_120:
  pushl $0
  pushl $120
  jmp alltraps
.globl trap_handler_121
trap_handler_121:
  pushl $0
  pushl $121
  jmp alltraps
.globl trap_handler_122
trap_handler_122:
  pushl $0
  pushl $122
  jmp alltraps
.globl trap_handler_123
trap_handler_123:
  pushl $0
  pushl $123
  jmp alltraps
.globl trap_handler_124
trap_handler_124:
  pushl $0
  pushl $124
  jmp alltraps
.globl trap_handler_125
trap_handler_125:
  pushl $0
  pushl $125
  jmp alltraps
.globl trap_handler_126
trap_handler_126:
  pushl $0
  pushl $126
  jmp alltraps
.globl trap_handler_127
trap_handler_127:
  pushl $0
  pushl $127
  jmp alltraps
.globl trap_handler_128
trap_handler_128:
  pushl $0
  pushl $128
  jmp alltraps
.globl trap_handler_129
trap_handler_129:
  pushl $0
  pushl $129
  jmp alltraps
.globl trap_handler_130
trap_handler_130:
  pushl $0
  pushl $130
  jmp alltraps
.globl trap_handler_131
trap_handler_131:
  pushl $0
  pushl $131
  jmp alltraps
.globl trap_handler_132
trap_handler_132:
  pushl $0
  pushl $132
  jmp alltraps
.globl trap_handler_133
trap_handler_133:
  pushl $0
  pushl $133
  jmp alltraps
.globl trap_handler_134
trap_handler_134:
  pushl $0
  pushl $134
  jmp alltraps
.globl trap_handler_135
trap_handler_135:
  pushl $0
  pushl $135
  jmp alltraps
.globl trap_handler_136
trap_handler_136:
  pushl $0
  pushl $136
  jmp alltraps
.globl trap_handler_137
trap_handler_137:
  pushl $0
  pushl $137
  jmp alltraps
.globl trap_handler_138
trap_handler_138:
  pushl $0
  pushl $138
  jmp alltraps
.globl trap_handler_139
trap_handler_139:
  pushl $0
  pushl $139
  jmp alltraps
.globl trap_handler_140
trap_handler_140:
  pushl $0
  pushl $140
  jmp alltraps
.globl trap_handler_141
trap_handler_141:
  pushl $0
  pushl $141
  jmp alltraps
.globl trap_handler_142
trap_handler_142:
  pushl $0
  pushl $142
  jmp alltraps
.globl trap_handler_143
trap_handler_143:
  pushl $0
  pushl $143
  jmp alltraps
.globl trap_handler_144
trap_handler_144:
  pushl $0
  pushl $144
  jmp alltraps
.globl trap_handler_145
trap_handler_145:
  pushl $0
  pushl $145
  jmp alltraps
.globl trap_handler_146
trap_handler_146:
  pushl $0
  pushl $146
  jmp alltraps
.globl trap_handler_147
trap_handler_147:
  pushl $0
  pushl $147
  jmp alltraps
.globl trap_handler_148
trap_handler_148:
  pushl $0
  pushl $148
  jmp alltraps
.globl trap_handler_149
trap_handler_149:
  pushl $0
  pushl $149
  jmp alltraps
.globl trap_handler_150
trap_handler_150:
  pushl $0
  pushl $150
  jmp alltraps
.globl trap_handler_151
trap_handler_151:
  pushl $0
  pushl $151
  jmp alltraps
.globl trap_handler_152
trap_handler_152:
  pushl $0
  pushl $152
  jmp alltraps
.globl trap_handler_153
trap_handler_153:
  pushl $0
  pushl $153
  jmp alltraps
.globl trap_handler_154
trap_handler_154:
  pushl $0
  pushl $154
  jmp alltraps
.globl trap_handler_155
trap_handler_155:
  pushl $0
  pushl $155
  jmp alltraps
.globl trap_handler_156
trap_handler_156:
  pushl $0
  pushl $156
  jmp alltraps
.globl trap_handler_157
trap_handler_157:
  pushl $0
  pushl $157
  jmp alltraps
.globl trap_handler_158
trap_handler_158:
  pushl $0
  pushl $158
  jmp alltraps
.globl trap_handler_159
trap_handler_159:
  pushl $0
  pushl $159
  jmp alltraps
.globl trap_handler_160
trap_handler_160:
  pushl $0
  pushl $160
  jmp alltraps
.globl trap_handler_161
trap_handler_161:
  pushl $0
  pushl $161
  jmp alltraps
.globl trap_handler_162
trap_handler_162:
  pushl $0
  pushl $162
  jmp alltraps
.globl trap_handler_163
trap_handler_163:
  pushl $0
  pushl $163
  jmp alltraps
.globl trap_handler_164
trap_handler_164:
  pushl $0
  pushl $164
  jmp alltraps
.globl trap_handler_165
trap_handler_165:
  pushl $0
  pushl $165
  jmp alltraps
.globl trap_handler_166
trap_handler_166:
  pushl $0
  pushl $166
  jmp alltraps
.globl trap_handler_167
trap_handler_167:
  pushl $0
  pushl $167
  jmp alltraps
.globl trap_handler_168
trap_handler_168:
  pushl $0
  pushl $168
  jmp alltraps
.globl trap_handler_169
trap_handler_169:
  pushl $0
  pushl $169
  jmp alltraps
.globl trap_handler_170
trap_handler_170:
  pushl $0
  pushl $170
  jmp alltraps
.globl trap_handler_171
trap_handler_171:
  pushl $0
  pushl $171
  jmp alltraps
.globl trap_handler_172
trap_handler_172:
  pushl $0
  pushl $172
  jmp alltraps
.globl trap_handler_173
trap_handler_173:
  pushl $0
  pushl $173
  jmp alltraps
.globl trap_handler_174
trap_handler_174:
  pushl $0
  pushl $174
  jmp alltraps
.globl trap_handler_175
trap_handler_175:
  pushl $0
  pushl $175
  jmp alltraps
.globl trap_handler_176
trap_handler_176:
  pushl $0
  pushl $176
  jmp alltraps
.globl trap_handler_177
trap_handler_177:
  pushl $0
  pushl $177
  jmp alltraps
.globl trap_handler_178
trap_handler_178:
  pushl $0
  pushl $178
  jmp alltraps
.globl trap_handler_179
trap_handler_179:
  pushl $0
  pushl $179
  jmp alltraps
.globl trap_handler_180
trap_handler_180:
  pushl $0
  pushl $180
  jmp alltraps
.globl trap_handler_181
trap_handler_181:
  pushl $0
  pushl $181
  jmp alltraps
.globl trap_handler_182
trap_handler_182:
  pushl $0
  pushl $182
  jmp alltraps
.globl trap_handler_183
trap_handler_183:
  pushl $0
  pushl $183
  jmp alltraps
.globl trap_handler_184
trap_handler_184:
  pushl $0
  pushl $184
  jmp alltraps
.globl trap_handler_185
trap_handler_185:
  pushl $0
  pushl $185
  jmp alltraps
.globl trap_handler_186
trap_handler_186:
  pushl $0
  pushl $186
  jmp alltraps
.globl trap_handler_187
trap_handler_187:
  pushl $0
  pushl $187
  jmp alltraps
.globl trap_handler_188
trap_handler_188:
  pushl $0
  pushl $188
  jmp alltraps
.globl trap_handler_189
trap_handler_189:
  pushl $0
  pushl $189
  jmp alltraps
.globl trap_handler_190
trap_handler_190:
  pushl $0
  pushl $190
  jmp alltraps
.globl trap_handler_191
trap_handler_191:
  pushl $0
  pushl $191
  jmp alltraps
.globl trap_handler_192
trap_handler_192:
  pushl $0
  pushl $192
  jmp alltraps
.globl trap_handler_193
trap_handler_193:
  pushl $0
  pushl $193
  jmp alltraps
.globl trap_handler_194
trap_handler_194:
  pushl $0
  pushl $194
  jmp alltraps
.globl trap_handler_195
trap_handler_195:
  pushl $0
  pushl $195
  jmp alltraps
.globl trap_handler_196
trap_handler_196:
  pushl $0
  pushl $196
  jmp alltraps
.globl trap_handler_197
trap_handler_197:
  pushl $0
  pushl $197
  jmp alltraps
.globl trap_handler_198
trap_handler_198:
  pushl $0
  pushl $198
  jmp alltraps
.globl trap_handler_199
trap_handler_199:
  pushl $0
  pushl $199
  jmp alltraps
.globl trap_handler_200
trap_handler_200:
  pushl $0
  pushl $200
  jmp alltraps
.globl trap_handler_201
trap_handler_201:
  pushl $0
  pushl $201
  jmp alltraps
.globl trap_handler_202
trap_handler_202:
  pushl $0
  pushl $202
  jmp alltraps
.globl trap_handler_203
trap_handler_203:
  pushl $0
  pushl $203
  jmp alltraps
.globl trap_handler_204
trap_handler_204:
  pushl $0
  pushl $204
  jmp alltraps
.globl trap_handler_205
trap_handler_205:
  pushl $0
  pushl $205
  jmp alltraps
.globl trap_handler_206
trap_handler_206:
  pushl $0
  pushl $206
  jmp alltraps
.globl trap_handler_207
trap_handler_207:
  pushl $0
  pushl $207
  jmp alltraps
.globl trap_handler_208
trap_handler_208:
  pushl $0
  pushl $208
  jmp alltraps
.globl trap_handler_209
trap_handler_209:
  pushl $0
  pushl $209
  jmp alltraps
.globl trap_handler_210
trap_handler_210:
  pushl $0
  pushl $210
  jmp alltraps
.globl trap_handler_211
trap_handler_211:
  pushl $0
  pushl $211
  jmp alltraps
.globl trap_handler_212
trap_handler_212:
  pushl $0
  pushl $212
  jmp alltraps
.globl trap_handler_213
trap_handler_213:
  pushl $0
  pushl $213
  jmp alltraps
.globl trap_handler_214
trap_handler_214:
  pushl $0
  pushl $214
  jmp alltraps
.globl trap_handler_215
trap_handler_215:
  pushl $0
  pushl $215
  jmp alltraps
.globl trap_handler_216
trap_handler_216:
  pushl $0
  pushl $216
  jmp alltraps
.globl trap_handler_217
trap_handler_217:
  pushl $0
  pushl $217
  jmp alltraps
.globl trap_handler_218
trap_handler_218:
  pushl $0
  pushl $218
  jmp alltraps
.globl trap_handler_219
trap_handler_219:
  pushl $0
  pushl $219
  jmp alltraps
.globl trap_handler_220
trap_handler_220:
  pushl $0
  pushl $220
  jmp alltraps
.globl trap_handler_221
trap_handler_221:
  pushl $0
  pushl $221
  jmp alltraps
.globl trap_handler_222
trap_handler_222:
  pushl $0
  pushl $222
  jmp alltraps
.globl trap_handler_223
trap_handler_223:
  pushl $0
  pushl $223
  jmp alltraps
.globl trap_handler_224
trap_handler_224:
  pushl $0
  pushl $224
  jmp alltraps
.globl trap_handler_225
trap_handler_225:
  pushl $0
  pushl $225
  jmp alltraps
.globl trap_handler_226
trap_handler_226:
  pushl $0
  pushl $226
  jmp alltraps
.globl trap_handler_227
trap_handler_227:
  pushl $0
  pushl $227
  jmp alltraps
.globl trap_handler_228
trap_handler_228:
  pushl $0
  pushl $228
  jmp alltraps
.globl trap_handler_229
trap_handler_229:
  pushl $0
  pushl $229
  jmp alltraps
.globl trap_handler_230
trap_handler_230:
  pushl $0
  pushl $230
  jmp alltraps
.globl trap_handler_231
trap_handler_231:
  pushl $0
  pushl $231
  jmp alltraps
.globl trap_handler_232
trap_handler_232:
  pushl $0
  pushl $232
  jmp alltraps
.globl trap_handler_233
trap_handler_233:
  pushl $0
  pushl $233
  jmp alltraps
.globl trap_handler_234
trap_handler_234:
  pushl $0
  pushl $234
  jmp alltraps
.globl trap_handler_235
trap_handler_235:
  pushl $0
  pushl $235
  jmp alltraps
.globl trap_handler_236
trap_handler_236:
  pushl $0
  pushl $236
  jmp alltraps
.globl trap_handler_237
trap_handler_237:
  pushl $0
  pushl $237
  jmp alltraps
.globl trap_handler_238
trap_handler_238:
  pushl $0
  pushl $238
  jmp alltraps
.globl trap_handler_239
trap_handler_239:
  pushl $0
  pushl $239
  jmp alltraps
.globl trap_handler_240
trap_handler_240:
  pushl $0
  pushl $240
  jmp alltraps
.globl trap_handler_241
trap_handler_241:
  pushl $0
  pushl $241
  jmp alltraps
.globl trap_handler_242
trap_handler_242:
  pushl $0
  pushl $242
  jmp alltraps
.globl trap_handler_243
trap_handler_243:
  pushl $0
  pushl $243
  jmp alltraps
.globl trap_handler_244
trap_handler_244:
  pushl $0
  pushl $244
  jmp alltraps
.globl trap_handler_245
trap_handler_245:
  pushl $0
  pushl $245
  jmp alltraps
.globl trap_handler_246
trap_handler_246:
  pushl $0
  pushl $246
  jmp alltraps
.globl trap_handler_247
trap_handler_247:
  pushl $0
  pushl $247
  jmp alltraps
.globl trap_handler_248
trap_handler_248:
  pushl $0
  pushl $248
  jmp alltraps
.globl trap_handler_249
trap_handler_249:
  pushl $0
  pushl $249
  jmp alltraps
.globl trap_handler_250
trap_handler_250:
  pushl $0
  pushl $250
  jmp alltraps
.globl trap_handler_251
trap_handler_251:
  pushl $0
  pushl $251
  jmp alltraps
.globl trap_handler_252
trap_handler_252:
  pushl $0
  pushl $252
  jmp alltraps
.globl trap_handler_253
trap_handler_253:
  pushl $0
  pushl $253
  jmp alltraps
.globl trap_handler_254
trap_handler_254:
  pushl $0
  pushl $254
  jmp alltraps
.globl trap_handler_255
trap_handler_255:
  pushl $0
  pushl $255
  jmp alltraps

# trap_handler_ table
.data
.globl trap_handler_array
trap_handler_array:
  .long trap_handler_0
  .long trap_handler_1
  .long trap_handler_2
  .long trap_handler_3
  .long trap_handler_4
  .long trap_handler_5
  .long trap_handler_6
  .long trap_handler_7
  .long trap_handler_8
  .long trap_handler_9
  .long trap_handler_10
  .long trap_handler_11
  .long trap_handler_12
  .long trap_handler_13
  .long trap_handler_14
  .long trap_handler_15
  .long trap_handler_16
  .long trap_handler_17
  .long trap_handler_18
  .long trap_handler_19
  .long trap_handler_20
  .long trap_handler_21
  .long trap_handler_22
  .long trap_handler_23
  .long trap_handler_24
  .long trap_handler_25
  .long trap_handler_26
  .long trap_handler_27
  .long trap_handler_28
  .long trap_handler_29
  .long trap_handler_30
  .long trap_handler_31
  .long trap_handler_32
  .long trap_handler_33
  .long trap_handler_34
  .long trap_handler_35
  .long trap_handler_36
  .long trap_handler_37
  .long trap_handler_38
  .long trap_handler_39
  .long trap_handler_40
  .long trap_handler_41
  .long trap_handler_42
  .long trap_handler_43
  .long trap_handler_44
  .long trap_handler_45
  .long trap_handler_46
  .long trap_handler_47
  .long trap_handler_48
  .long trap_handler_49
  .long trap_handler_50
  .long trap_handler_51
  .long trap_handler_52
  .long trap_handler_53
  .long trap_handler_54
  .long trap_handler_55
  .long trap_handler_56
  .long trap_handler_57
  .long trap_handler_58
  .long trap_handler_59
  .long trap_handler_60
  .long trap_handler_61
  .long trap_handler_62
  .long trap_handler_63
  .long trap_handler_64
  .long trap_handler_65
  .long trap_handler_66
  .long trap_handler_67
  .long trap_handler_68
  .long trap_handler_69
  .long trap_handler_70
  .long trap_handler_71
  .long trap_handler_72
  .long trap_handler_73
  .long trap_handler_74
  .long trap_handler_75
  .long trap_handler_76
  .long trap_handler_77
  .long trap_handler_78
  .long trap_handler_79
  .long trap_handler_80
  .long trap_handler_81
  .long trap_handler_82
  .long trap_handler_83
  .long trap_handler_84
  .long trap_handler_85
  .long trap_handler_86
  .long trap_handler_87
  .long trap_handler_88
  .long trap_handler_89
  .long trap_handler_90
  .long trap_handler_91
  .long trap_handler_92
  .long trap_handler_93
  .long trap_handler_94
  .long trap_handler_95
  .long trap_handler_96
  .long trap_handler_97
  .long trap_handler_98
  .long trap_handler_99
  .long trap_handler_100
  .long trap_handler_101
  .long trap_handler_102
  .long trap_handler_103
  .long trap_handler_104
  .long trap_handler_105
  .long trap_handler_106
  .long trap_handler_107
  .long trap_handler_108
  .long trap_handler_109
  .long trap_handler_110
  .long trap_handler_111
  .long trap_handler_112
  .long trap_handler_113
  .long trap_handler_114
  .long trap_handler_115
  .long trap_handler_116
  .long trap_handler_117
  .long trap_handler_118
  .long trap_handler_119
  .long trap_handler_120
  .long trap_handler_121
  .long trap_handler_122
  .long trap_handler_123
  .long trap_handler_124
  .long trap_handler_125
  .long trap_handler_126
  .long trap_handler_127
  .long trap_handler_128
  .long trap_handler_129
  .long trap_handler_130
  .long trap_handler_131
  .long trap_handler_132
  .long trap_handler_133
  .long trap_handler_134
  .long trap_handler_135
  .long trap_handler_136
  .long trap_handler_137
  .long trap_handler_138
  .long trap_handler_139
  .long trap_handler_140
  .long trap_handler_141
  .long trap_handler_142
  .long trap_handler_143
  .long trap_handler_144
  .long trap_handler_145
  .long trap_handler_146
  .long trap_handler_147
  .long trap_handler_148
  .long trap_handler_149
  .long trap_handler_150
  .long trap_handler_151
  .long trap_handler_152
  .long trap_handler_153
  .long trap_handler_154
  .long trap_handler_155
  .long trap_handler_156
  .long trap_handler_157
  .long trap_handler_158
  .long trap_handler_159
  .long trap_handler_160
  .long trap_handler_161
  .long trap_handler_162
  .long trap_handler_163
  .long trap_handler_164
  .long trap_handler_165
  .long trap_handler_166
  .long trap_handler_167
  .long trap_handler_168
  .long trap_handler_169
  .long trap_handler_170
  .long trap_handler_171
  .long trap_handler_172
  .long trap_handler_173
  .long trap_handler_174
  .long trap_handler_175
  .long trap_handler_176
  .long trap_handler_177
  .long trap_handler_178
  .long trap_handler_179
  .long trap_handler_180
  .long trap_handler_181
  .long trap_handler_182
  .long trap_handler_183
  .long trap_handler_184
  .long trap_handler_185
  .long trap_handler_186
  .long trap_handler_187
  .long trap_handler_188
  .long trap_handler_189
  .long trap_handler_190
  .long trap_handler_191
  .long trap_handler_192
  .long trap_handler_193
  .long trap_handler_194
  .long trap_handler_195
  .long trap_handler_196
  .long trap_handler_197
  .long trap_handler_198
  .long trap_handler_199
  .long trap_handler_200
  .long trap_handler_201
  .long trap_handler_202
  .long trap_handler_203
  .long trap_handler_204
  .long trap_handler_205
  .long trap_handler_206
  .long trap_handler_207
  .long trap_handler_208
  .long trap_handler_209
  .long trap_handler_210
  .long trap_handler_211
  .long trap_handler_212
  .long trap_handler_213
  .long trap_handler_214
  .long trap_handler_215
  .long trap_handler_216
  .long trap_handler_217
  .long trap_handler_218
  .long trap_handler_219
  .long trap_handler_220
  .long trap_handler_221
  .long trap_handler_222
  .long trap_handler_223
  .long trap_handler_224
  .long trap_handler_225
  .long trap_handler_226
  .long trap_handler_227
  .long trap_handler_228
  .long trap_handler_229
  .long trap_handler_230
  .long trap_handler_231
  .long trap_handler_232
  .long trap_handler_233
  .long trap_handler_234
  .long trap_handler_235
  .long trap_handler_236
  .long trap_handler_237
  .long trap_handler_238
  .long trap_handler_239
  .long trap_handler_240
  .long trap_handler_241
  .long trap_handler_242
  .long trap_handler_243
  .long trap_handler_244
  .long trap_handler_245
  .long trap_handler_246
  .long trap_handler_247
  .long trap_handler_248
  .long trap_handler_249
  .long trap_handler_250
  .long trap_handler_251
  .long trap_handler_252
  .long trap_handler_253
  .long trap_handler_254
  .long trap_handler_255
