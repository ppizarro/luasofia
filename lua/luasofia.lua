
local core = require "luasofia.core"

local function struct_new(s_proto, ptr)
  local buf = core.buffer(ptr or s_proto.size)
  local function struct_get(_, key)
    if s_proto.offsets[key] then
      return buf:get(s_proto.offsets[key] + 1, s_proto.types[key])
    else 
      error("field " .. key .. " does not exist")
    end
  end
  local function struct_set(_, key, val)
    if s_proto.offsets[key] then
      buf:set(s_proto.offsets[key] + 1, val, s_proto.types[key])
    else
      error("field " .. key .. " does not exist")
    end
  end
  return setmetatable({}, { __index = struct_get, __newindex = struct_set,
                            __call = function () return buf end })
end

function defstruct(t)
  local off = 0
  local names, offsets, types = {}, {}, {}
  for _, field in ipairs(t) do
    local name, type = field[1], field[2]
    names[#names + 1] = name
    off = math.ceil(off / core.align(type)) * core.align(type)
    offsets[name] = off
    types[name] = type
    off = off + core.sizeof(type)
  end
  return { names = names, offsets = offsets, types = types, size = off, new = struct_new }
end

su = require "luasofia.su"
nua = require "luasofia.nua"
sip = require "luasofia.sip"
soa = require "luasofia.soa"

--[[
url_t = defstruct{
    { "pad",      "short"  },
    { "type",     "char"   },
    { "root",     "char"   },
    { "scheme",   "string" },
    { "user",     "string" },
    { "password", "string" },
    { "host",     "string" },
    { "port",     "string" },
    { "path",     "string" },
    { "params",   "string" },
    { "headers",  "string" },
    { "fragment", "string" }
}
--]]

--[[
sip_t = defstruct{
  { "h_succ", "pointer" }, -- Pointer to succeeding fragment.
  { "h_prev", "pointer" }, -- Pointer to preceeding fragment.
  { "h_class", "pointer" }, -- Header class.
  { "h_data", "pointer" }, -- Fragment data */
  usize_t             h_len;    -- Fragment length (including CRLF)

  { "sip_next", "pointer" }, -- Dummy link to msgfrag
  { "sip_user", "pointer" }, -- Application data
  unsigned                   sip_size;          /**< Size of structure */
  int                        sip_flags;         /**< Parser flags */

  { "sip_error", "pointer" }, -- Erroneous headers

  -- Pseudoheaders
  { "sip_request", "pointer" }, -- Request line
  { "sip_status", "pointer" }, -- Status line

  -- Headers start here
  { "sip_via", "pointer" }, -- Via (v)
  { "sip_route", "pointer" }, -- Route
  { "sip_record_route", "pointer" }, -- Record-Route
  { "sip_max_forwards", "pointer" }, -- Max-Forwards
  { "sip_proxy_require", "pointer" }, -- Proxy-Require

  { "sip_from", "pointer" }, -- From (f)
  { "sip_to", "pointer" }, -- To (t)
  { "sip_call_id", "pointer" }, -- Call-ID (i)
  { "sip_cseq", "pointer" }, -- CSeq
  { "sip_contact", "pointer" }, -- Contact (m)
  { "sip_rseq", "pointer" }, -- RSeq
  { "sip_rack", "pointer" }, -- RAck

  /* Caller Preferences */
  { "sip_request_disposition", "pointer" }, --sip_request_disposition_t *sip_request_disposition;
                                                /**< Request-Disposition (d) */
  { "", "pointer" }, --sip_accept_contact_t      *sip_accept_contact;/**< Accept-Contact (a) */
  { "", "pointer" }, --sip_reject_contact_t      *sip_reject_contact;/**< Reject-Contact (j) */

 { "", "pointer" }, --sip_expires_t             *sip_expires;       /**< Expires */
  { "", "pointer" }, --sip_date_t                *sip_date;          /**< Date */
  { "", "pointer" }, --sip_retry_after_t         *sip_retry_after;   /**< Retry-After */
  { "", "pointer" }, --sip_timestamp_t           *sip_timestamp;     /**< Timestamp */
  { "", "pointer" }, --sip_min_expires_t         *sip_min_expires;   /**< Min-Expires */

  { "", "pointer" }, --sip_subject_t             *sip_subject;       /**< Subject (s) */
  { "", "pointer" }, --sip_priority_t            *sip_priority;      /**< Priority */

  { "", "pointer" }, --sip_call_info_t           *sip_call_info;     /**< Call-Info */
  { "", "pointer" }, --sip_organization_t        *sip_organization;  /**< Organization */
  { "", "pointer" }, --sip_server_t              *sip_server;        /**< Server */
  { "", "pointer" }, --sip_user_agent_t          *sip_user_agent;    /**< User-Agent */
  { "", "pointer" }, --sip_in_reply_to_t         *sip_in_reply_to;   /**< In-Reply-To */

  { "", "pointer" }, --sip_accept_t              *sip_accept;        /**< Accept */
  { "", "pointer" }, --sip_accept_encoding_t     *sip_accept_encoding; /**< Accept-Encoding */
  { "", "pointer" }, --sip_accept_language_t     *sip_accept_language; /**< Accept-Language */

  { "", "pointer" }, --sip_allow_t               *sip_allow;         /**< Allow */
  { "", "pointer" }, --sip_require_t             *sip_require;       /**< Require */
  { "", "pointer" }, --sip_supported_t           *sip_supported;     /**< Supported (k) */
  { "", "pointer" }, --sip_unsupported_t         *sip_unsupported;   /**< Unsupported */

  /* RFC 3265 */
  { "", "pointer" }, --sip_event_t               *sip_event;         /**< Event (o) */
  { "", "pointer" }, --sip_allow_events_t        *sip_allow_events;  /**< Allow-Events (u) */
  { "", "pointer" }, --sip_subscription_state_t  *sip_subscription_state;
                                /**< Subscription-State */

  { "", "pointer" }, --sip_proxy_authenticate_t  *sip_proxy_authenticate;
                                /**< Proxy-Authenticate */
  { "", "pointer" }, --sip_proxy_authentication_info_t *sip_proxy_authentication_info;
                                /**< Proxy-Authentication-Info */
  { "", "pointer" }, --sip_proxy_authorization_t *sip_proxy_authorization;
                               /**< Proxy-Authorization */
  { "", "pointer" }, --sip_authorization_t       *sip_authorization;
                                /**< Authorization */
  { "", "pointer" }, --sip_www_authenticate_t    *sip_www_authenticate;
                                /**< WWW-Authenticate */
  { "", "pointer" }, --sip_authentication_info_t *sip_authentication_info;
                                /**< Authentication-Info */
  { "", "pointer" }, --sip_error_info_t          *sip_error_info;    /**< Error-Info */
  { "", "pointer" }, --sip_warning_t             *sip_warning;       /**< Warning */

  /* RFC 3515 */
  { "", "pointer" }, --sip_refer_to_t            *sip_refer_to;      /**< Refer-To (r) */
  { "", "pointer" }, --sip_referred_by_t         *sip_referred_by;   /**< Referred-By (b) */
  { "", "pointer" }, --sip_replaces_t            *sip_replaces;      /**< Replaces */

  /* draft-ietf-sip-session-timer */
  { "", "pointer" }, --sip_session_expires_t     *sip_session_expires;
                                /**< Session-Expires (x) */
  { "", "pointer" }, --sip_min_se_t              *sip_min_se;        /**< Min-SE */

  { "", "pointer" }, --sip_path_t                *sip_path;        /**< Path */
  { "", "pointer" }, --sip_service_route_t       *sip_service_route; /**< Service-Route */

  { "", "pointer" }, --sip_reason_t              *sip_reason;        /**< Reason */

  { "", "pointer" }, --sip_security_client_t     *sip_security_client; /**< Security-Client */
  { "", "pointer" }, --sip_security_server_t     *sip_security_server; /**< Security-Server */
  { "", "pointer" }, --sip_security_verify_t     *sip_security_verify; /**< Security-Verify */

  { "", "pointer" }, --sip_privacy_t             *sip_privacy; /**< Privacy */

  { "", "pointer" }, --sip_etag_t                *sip_etag;          /**< SIP-ETag */
  { "", "pointer" }, --sip_if_match_t            *sip_if_match;      /**< SIP-If-Match */

  /* Entity headers */
  { "", "pointer" }, --sip_mime_version_t        *sip_mime_version;  /**< MIME-Version */
  { "", "pointer" }, --sip_content_type_t        *sip_content_type;  /**< Content-Type (c) */
  { "", "pointer" }, --sip_content_encoding_t    *sip_content_encoding;
                                /**< Content-Encoding (e) */
  { "", "pointer" }, --sip_content_language_t    *sip_content_language; /**< Content-Language */
  { "", "pointer" }, --sip_content_disposition_t *sip_content_disposition;
                                /**< Content-Disposition */
  { "", "pointer" }, --sip_content_length_t      *sip_content_length;/**< Content-Length (l) */

  /* === Headers end here */

  { "", "pointer" }, --sip_unknown_t             *sip_unknown;       /**< Unknown headers */
  { "", "pointer" }, --sip_separator_t           *sip_separator;
                                /**< Separator between headers and payload */
  { "", "pointer" }, --sip_payload_t             *sip_payload;       /**< Message payload */
  { "", "pointer" }, --msg_multipart_t           *sip_multipart;     /**< Multipart MIME payload */
}
]]--
