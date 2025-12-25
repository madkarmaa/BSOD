import * as z from 'zod';

const env = z.object({
  VT_API_KEY: z.string(),
  GITHUB_OUTPUT: z.string().optional() // don't assume it's CI
}).parse(process.env);

const file = Bun.file("Release/BSOD.exe");
const hash = new Bun.CryptoHasher("sha256").update(await file.arrayBuffer()).digest("hex");

const form = new FormData();
form.append("file", file, "BSOD.exe");

const res = await fetch('https://www.virustotal.com/api/v3/files', {
  method: 'POST',
  headers: {
    accept: 'application/json',
    'x-apikey': env.VT_API_KEY
  },
  body: form
});

if (!res.ok) {
  console.error(`Error uploading file: ${res.status} ${res.statusText}`);
  console.error(await res.text());
  process.exit(1);
}

const url = `https://www.virustotal.com/gui/file/${hash}`;
console.log(`VirusTotal URL: ${url}`);

if (env.GITHUB_OUTPUT) {
  const fs = await import('node:fs');
  fs.appendFileSync(env.GITHUB_OUTPUT, `url=${url}\n`);
}