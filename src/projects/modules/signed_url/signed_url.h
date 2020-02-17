#pragma once

#include <base/ovsocket/socket_address.h>
#include <base/ovlibrary/ovlibrary.h>

enum class SignedUrlType
{
    // Type0 : Des.Decrypt(Base64.Decode("[url],[client ip],[token expired time],[stream expired time]", key, ECB Mode, Pkcs5 Padding))
    Type0, 
    // No defined yet
    Type1,  
};

class SignedUrl
{
public:
	static std::shared_ptr<const SignedUrl> Load(SignedUrlType type, const ov::String &key, const ov::String &data);

    const ov::String&       GetUrl() const;
    const ov::String&       GetClientIP() const;
    uint64_t                GetTokenExpiredTime() const;
    uint64_t                GetStreamExpiredTime() const;
    bool                    IsAllowedClient(const ov::SocketAddress &address) const;
    bool                    IsTokenExpired() const;
    bool                    IsStreamExpired() const;

private:

    bool ProcessType0(const ov::String &key, const ov::String &data);
    bool Parse(const ov::String &plain_string);

    uint64_t	GetNowMS() const;

    ov::String  _key;
    ov::String  _full_string;

    ov::String  _url;
    ov::String  _client_ip;
    uint64_t    _token_expired_time;
    uint64_t    _stream_expired_time;
};
