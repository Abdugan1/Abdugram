SELECT m.*
FROM messages m
WHERE m.chat_id IN (
    SELECT cu.chat_id
    FROM chat_users cu
    WHERE cu.user_id = :user_id
)
AND m.updated_at >= :last_updated_at;
