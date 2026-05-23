This is the structure of the game.
asset folder handles assets with child folders sound, image.
client folder handles things clients are able to do
server folder handles data from the cleint and saves it
network is for the establishment inbetween.
gui is for non 3d ui.
This is a raycasted voxel game, teardown and physics simulated with connections. with multiplyer stuff in the future.
look in previous attmp leftovers in readme or structidea for ideas.
client: Rendering, Detection, Animation, Assets
Server: Main authority client not allowed many authoritys, security, physics, servers, generation, host, join, solo.
Network: status, cenneting to browser.
GUI: Menus, developer interface

No block size complications, its just the grid size.

Side Notes: 
Blocks data uses the bottom left down corenr as thier location(xyz).
