/*
 * Copyright (c) 2008-2016 Juli Mallett. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef	IO_NET_TCP_CLIENT_H
#define	IO_NET_TCP_CLIENT_H

#include <common/thread/mutex.h>

#include <event/cancellation.h>

#include <io/socket/socket.h>

class TCPClient {
	friend class DestroyThread;

	LogHandle log_;
	Mutex mtx_;
	SocketImpl impl_;
	SocketAddressFamily family_;
	Socket *socket_;

	SimpleCallback::Method<TCPClient> close_complete_;
	Action *close_action_;

	EventCallback::Method<TCPClient> connect_complete_;
	Cancellation<TCPClient> connect_cancel_;
	Action *connect_action_;
	SocketEventCallback *connect_callback_;

	TCPClient(SocketImpl, SocketAddressFamily);
	~TCPClient();

	Action *connect(const std::string&, const std::string&, SocketEventCallback *);
	void connect_cancel(void);
	void connect_complete(Event);

	void close_complete(void);

public:
	static Action *connect(SocketImpl, SocketAddressFamily, const std::string&, SocketEventCallback *);
	static Action *connect(SocketImpl, SocketAddressFamily, const std::string&, const std::string&, SocketEventCallback *);
};

#endif /* !IO_NET_TCP_CLIENT_H */
