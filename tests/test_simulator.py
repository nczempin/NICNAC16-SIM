import subprocess
import os


def test_simulator_runs():
    bin_path = os.path.join('build', 'nicnac16_sim')
    assert os.path.exists(bin_path), 'Simulator binary not built'
    result = subprocess.run([bin_path], capture_output=True, text=True)
    assert result.returncode == 0
    assert '===== END OF LINE =====' in result.stdout
