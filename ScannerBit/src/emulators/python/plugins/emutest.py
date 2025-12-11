import emulator_plugin as eplug
import numpy as np


class Test:#(eplug.emulator):

    __version__="1.0.0"

    def __init__(self, **options):

        # super().__init__()
        print("starting test emulator plugin x")

    def train(self, x, y, sigs):

        print(f"training inputed points, x: {x}; y: {y}; sigs: {sigs}")

        return

    def predict(self, x):

        print(f"predicted input, x: {x}")
        
        return (np.array([3.5]), np.array([0.2]))

__plugins__={"emutest": Test}
