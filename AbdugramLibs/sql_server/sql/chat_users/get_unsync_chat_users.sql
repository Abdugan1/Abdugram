SELECT cu.*
FROM chat_users cu
WHERE cu.chat_id IN (
    SELECT chat_id
    FROM chat_users
    WHERE user_id = :user_id
)
AND cu.chat_id = :chat_id
AND cu.updated_at >= :last_updated_at;
