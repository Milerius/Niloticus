#pragma once

namespace niloticus
{
    enum e_coin_type
    {
        QRC20      = 0,
        ERC20      = 1,
        UTXO       = 2,
        SmartChain = 3,
        Disabled   = 4,
        All        = 5,
        Size       = 6
    };
}