[ ] Identity
    [x] Génération Ed25519
    [x] Sauvegarde identity.key
    [x] Sauvegarde identity.pub
    [x] uid = SHA256(pubkey)


[ ] Format binaire des paquets
[ ] ip_request / ip_response
[ ] Signatures




------------------------------------------
[ ] Serialization
    [ ] Définir format binaire réseau
    [ ] Endianness
    [ ] Helpers encode/decode

[ ] Crypto
    [ ] Signature de messages
    [ ] Vérification signatures
    [ ] DH (X25519)
    [ ] AEAD pour payloads privés

[ ] IP Solver
    [ ] Définir ip_request
    [ ] Définir ip_response
    [ ] request_id
    [ ] timestamp + expiration
    [ ] Thread ipsolver
    [ ] Vérification uid/pubkey/signature
    [ ] Chiffrement réponse IP

[ ] DHT
    [ ] Node ID
    [ ] Table de routage
    [ ] PING / PONG
    [ ] STORE
    [ ] FIND_VALUE
    [ ] Réplication
    [ ] Expiration records

[ ] Contacts
    [ ] Ajouter contact
    [ ] Associer uid -> pubkey
    [ ] Vérification confiance

[ ] Messaging
    [ ] Session peer-to-peer
    [ ] Handshake
    [ ] Envoi message
    [ ] Réception message
    [ ] Chiffrement E2E

[ ] Persistence
    [ ] Contacts
    [ ] Cache DHT
    [ ] Paramètres

[ ] CLI
    [ ] login
    [ ] add-contact
    [ ] resolve
    [ ] send
    [ ] receive