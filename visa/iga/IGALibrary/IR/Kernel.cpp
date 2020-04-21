/*===================== begin_copyright_notice ==================================

Copyright (c) 2017 Intel Corporation

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


======================= end_copyright_notice ==================================*/

#include "Kernel.hpp"

using namespace iga;

Kernel::Kernel(const Model &model)
  : m_model(model)
  , m_mem(4096)
{
}

Kernel::~Kernel()
{
    // Since in a kernel blocks are allocated using the memory pool,
    // when the Kernel is freed, the memory pool is deleted and destructors
    // for Blocks are never called.  This means the InstList's memory pools
    // was never deleted and we need to do it here.
    //
    // Also, Instruction's fields with destructors need running
    // (e.g. m_comment)
    for (Block *bb : m_blocks) {
        bb->~Block();
    }
}

size_t Kernel::getInstructionCount() const
{
    size_t n = 0;
    for (const Block *b : getBlockList()) {
        n += b->getInstList().size();
    }
    return n;
}


Block *Kernel::createBlock()
{
    return new(&m_mem)Block();
}


void Kernel::appendBlock(Block *blk)
{
    m_blocks.push_back(blk);
}


Instruction *Kernel::createBasicInstruction(
    const OpSpec &op,
    const Predication &predOpnd,
    const RegRef &flagReg,
    ExecSize execSize,
    ChannelOffset chOff,
    MaskCtrl ectr,
    FlagModifier condMod)
{
    Instruction *inst = new(&m_mem)Instruction(
        op,
        execSize,
        chOff,
        ectr);
    inst->setPredication(predOpnd);
    inst->setFlagModifier(condMod);
    inst->setFlagReg(flagReg);

    return inst;
}


Instruction *Kernel::createBranchInstruction(
    const OpSpec &op,
    const Predication &predOpnd,
    const RegRef &flagReg,
    ExecSize execSize,
    ChannelOffset chOff,
    MaskCtrl ectr,
    BranchCntrl brnch)
{
    Instruction *inst = new(&m_mem)Instruction(
        op,
        execSize,
        chOff,
        ectr);

    inst->setBranchCtrl(brnch);
    inst->setPredication(predOpnd);
    inst->setFlagReg(flagReg);

    return inst;
}


Instruction *Kernel::createSendInstruction(
    const OpSpec &op,
    const Predication &predOpnd,
    const RegRef &flagReg,
    ExecSize execSize,
    ChannelOffset chOff,
    MaskCtrl ectr,
    const SendDesc &extDesc,
    const SendDesc &msgDesc
    )
{
    Instruction *inst = new(&m_mem)Instruction(
        op,
        execSize,
        chOff,
        ectr);

    inst->setPredication(predOpnd);
    inst->setFlagReg(flagReg);

    inst->setMsgDesc(msgDesc);
    inst->setExtMsgDesc(extDesc);

    return inst;
}


Instruction *Kernel::createNopInstruction()
{
    Instruction *inst = new(&m_mem)Instruction(
        m_model.lookupOpSpec(Op::NOP),
        ExecSize::SIMD1,
        ChannelOffset::M0,
        MaskCtrl::NORMAL);

    const Predication predOpnd;
    inst->setPredication(predOpnd);
    inst->setFlagModifier(FlagModifier::NONE);
    inst->setFlagReg(REGREF_ZERO_ZERO);

    return inst;
}


Instruction *Kernel::createIllegalInstruction()
{
    Instruction *inst = new(&m_mem)Instruction(
        m_model.lookupOpSpec(Op::ILLEGAL),
        ExecSize::SIMD1,
        ChannelOffset::M0,
        MaskCtrl::NORMAL);

    const Predication predOpnd;
    inst->setPredication(predOpnd);
    inst->setFlagModifier(FlagModifier::NONE);
    inst->setFlagReg(REGREF_ZERO_ZERO);

    return inst;
}

static Instruction *createSyncInstruction(SWSB &sw, const OpSpec &ops, MemManager &mem)
{
    Instruction *inst = new(&mem)Instruction(
        ops,
        ExecSize::SIMD8,
        ChannelOffset::M0,
        MaskCtrl::NOMASK);

    const Predication predOpnd;
    inst->setPredication(predOpnd);
    inst->setFlagModifier(FlagModifier::NONE);
    inst->setFlagReg(REGREF_ZERO_ZERO);
    inst->setSWSB(sw);
    inst->setSource(SourceIndex::SRC0, Operand::SRC_REG_NULL_UD);

    return inst;
}
Instruction *Kernel::createSyncNopInstruction(SWSB sw)
{
    return createSyncInstruction(sw, m_model.lookupOpSpec(Op::SYNC_NOP), m_mem);
}
Instruction *Kernel::createSyncAllRdInstruction(SWSB sw)
{
    return createSyncInstruction(sw, m_model.lookupOpSpec(Op::SYNC_ALLRD), m_mem);
}
Instruction *Kernel::createSyncAllWrInstruction(SWSB sw)
{
    return createSyncInstruction(sw, m_model.lookupOpSpec(Op::SYNC_ALLWR), m_mem);
}