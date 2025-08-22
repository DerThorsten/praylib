let ctx;
let running = true;

onmessage = (e) => {
  if (e.data.canvas) {
    ctx = e.data.canvas.getContext("2d");
    requestAnimationFrame(drawFrame);
  }
  if (e.data.stop) {
    running = false;
    ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
  }
};

function drawFrame() {
  if (!running) {
    console.log("Overlay worker stopped, clearing canvas");
    return;
  }

  const w = ctx.canvas.width;
  const h = ctx.canvas.height;

  ctx.clearRect(0, 0, w, h);

  // darkened overlay
  ctx.fillStyle = "rgba(0,0,0,0.5)";
  ctx.fillRect(0, 0, w, h);

  // text
  ctx.fillStyle = "white";
  ctx.font = "28px sans-serif";
  ctx.textAlign = "center";
  ctx.fillText("Loading...", w / 2, h / 2);

  // animated pulsing circle
  const t = Date.now() / 600;
  ctx.beginPath();
  ctx.arc(w / 2, h / 2 + 40, 20 + 5 * Math.sin(t), 0, Math.PI * 2);
  ctx.fillStyle = "orange";
  ctx.fill();

  requestAnimationFrame(drawFrame);
}