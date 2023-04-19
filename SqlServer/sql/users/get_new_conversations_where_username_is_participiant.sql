SELECT c.*
FROM conversations c
JOIN participants p ON c.id = p.conversation_id
WHERE p.user_id = :userId AND c.updated_at > :lastUpdate_;
