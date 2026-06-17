# Messenger

A decentralized peer-to-peer messaging system written in C.

Messenger is built around a simple idea:

> every user owns a cryptographic identity and communicates directly with other peers, without relying on a central authority.

The project focuses on simplicity, transparency and protocol design rather than feature accumulation.

---

## Architecture

Messenger is composed of three core layers:

### Identity

Each peer owns a long-term cryptographic identity:

- private key
- public key
- unique identifier

The identifier is derived from the public key and serves as the canonical identity within the network.

### Discovery

Peer discovery is performed through a distributed hash table (DHT).

The DHT is only responsible for locating peers and resolving network information.

It is not used for message storage.

### Communication

Once two peers discover each other, communication occurs directly between them.

All authentication and encryption are performed at the protocol level.