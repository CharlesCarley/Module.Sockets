/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#pragma once
#include <functional>
#include "Sockets/PlatformSocket.h"
#include "Threads/CriticalSection.h"
#include "Threads/Mutex.h"
#include "Utils/Definitions.h"

namespace Rt2::Sockets
{
    class ServerThread;

    using MessageFunction = std::function<void(const String& message)>;

    class ServerSocket
    {
    private:
        friend class ServerThread;


        mutable Threads::CriticalSection _sec{};
        Net::Socket                      _server{Net::InvalidSocket};
        I8                               _status{-1};
        ServerThread*                    _main{nullptr};
        MessageFunction                  _message{nullptr};

        void dispatch(const String& msg) const;

    public:
        ServerSocket(const String& ipv4, uint16_t port);
        ~ServerSocket();

        void onMessageReceived(const MessageFunction& function);

        void start();

        bool isOpen() const;

    private:
        void open(const String& ipv4, uint16_t port);
    };


    inline bool ServerSocket::isOpen() const
    {
        return _status == 0;
    }


}  // namespace Rt2::Sockets