/**
 * Loads environment variables from .env file
 * @returns {Object} Object containing environment variables
 */
async function loadEnv() {
    try {
        const response = await fetch("../.env");
        const text = await response.text();
        
        const env = {};
        text.split("\n").forEach(line => {
            const match = line.match(/^([^=]+)="([^"]*)"$/);
            if (match) {
                env[match[1]] = match[2];
            }
        });
        
        return env;
    } catch (error) {
        console.error("Error loading .env file:", error);
        return {};
    }
}

// Make env variables available globally
window.ENV = {};