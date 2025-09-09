import os
from telethon import TelegramClient

# Load environment variables
API_ID = int(os.getenv("API_ID", "YOUR_API_ID"))
API_HASH = os.getenv("API_HASH", "YOUR_API_HASH")
BOT_TOKEN = os.getenv("BOT_TOKEN", None)

# Your channel username or ID
CHANNEL_USERNAME = os.getenv("CHANNEL_USERNAME", "your_private_channel_username")

video_path = "final_output.mp4"

# Create the client
client = TelegramClient("session_name", API_ID, API_HASH)

async def main():
    print("Sending video to Telegram...")
    await client.send_file(CHANNEL_USERNAME, video_path, caption="Here is the edited video")
    print("Video sent successfully!")

with client:
    client.loop.run_until_complete(main())
